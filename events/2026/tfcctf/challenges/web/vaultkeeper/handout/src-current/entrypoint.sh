#!/bin/bash
set -e

EXPECT="2.4.56"
AVER=$(apache2 -v 2>/dev/null | grep -oP 'Apache/\K[0-9.]+' || echo 0.0.0)
if [ "$AVER" != "$EXPECT" ]; then
  echo "[FATAL] httpd $AVER does not match the pinned appliance build ($EXPECT); aborting." >&2
  exit 1
fi

if [ -n "$FLAG" ]; then echo -n "$FLAG" > /flag.txt; fi
chmod 0644 /flag.txt

mkdir -p /var/www/private
[ -f /var/www/private/cap.key ]  || head -c 32 /dev/urandom | base64 | tr -d '=+/\n' | head -c 16 > /var/www/private/cap.key
[ -f /var/www/private/cap.mask ] || head -c 24 /dev/urandom | base64 | tr -d '=+/\n' | head -c 16 > /var/www/private/cap.mask
if [ ! -f /var/www/private/token.secret ]; then
  L=$(( 28 + $(od -An -N1 -tu1 /dev/urandom | tr -d ' ') % 13 ))
  head -c 96 /dev/urandom | base64 | tr -d '=+/\n' | head -c "$L" > /var/www/private/token.secret
fi
chown -R www-data:www-data /var/www/private
chmod 0640 /var/www/private/cap.key /var/www/private/cap.mask /var/www/private/token.secret
export VK_CAP_KEY="$(cat /var/www/private/cap.key)"
export VK_TOKEN_SECRET="$(cat /var/www/private/token.secret)"

if [ ! -d /var/lib/mysql/mysql ]; then
  echo "[*] initializing mariadb data dir"
  mariadb-install-db --user=mysql --datadir=/var/lib/mysql >/dev/null 2>&1 || \
    mysql_install_db --user=mysql --datadir=/var/lib/mysql >/dev/null 2>&1
fi
mkdir -p /var/lib/mysql-files && chown -R mysql:mysql /var/lib/mysql /var/lib/mysql-files

echo "[*] starting mariadb"
mysqld_safe --datadir=/var/lib/mysql >/dev/null 2>&1 &

echo -n "[*] waiting for mysql"
for i in $(seq 1 60); do
  if mysqladmin ping --silent 2>/dev/null; then echo " up"; break; fi
  echo -n "."; sleep 1
done

echo "[*] applying schema"
mysql < /docker-entrypoint-init.sql || true

echo "[*] starting php-fpm"
php-fpm -D
for i in $(seq 1 20); do (echo > /dev/tcp/127.0.0.1/9000) 2>/dev/null && break; sleep 0.3; done

echo "[*] starting apache"
exec apache2-foreground
