FROM php:8.2.12-fpm-bullseye@sha256:9ccbbbc3a590278d0236a2dd20ad79a04ef056d089def32da13100d213bc78c4 AS fpm

FROM php:8.2.12-apache-bullseye@sha256:7631926a8eef7bda1aa9719ba097b581edfe6a1a5638604b68b2829a42d87c19

COPY --from=fpm /usr/local/sbin/php-fpm /usr/local/sbin/php-fpm
COPY --from=fpm /usr/local/etc/php-fpm.conf /usr/local/etc/php-fpm.conf
COPY --from=fpm /usr/local/etc/php-fpm.d/ /usr/local/etc/php-fpm.d/

RUN apt-get update \
 && apt-get install -y --no-install-recommends mariadb-server default-mysql-client curl \
 && docker-php-ext-install pdo_mysql >/dev/null \
 && apt-mark hold apache2 apache2-bin apache2-data \
 && apt-get clean && rm -rf /var/lib/apt/lists/*

ENV APACHE_DOCUMENT_ROOT=/var/www/html/public
RUN a2dismod php8.2 2>/dev/null || true; \
    a2enmod proxy proxy_fcgi rewrite headers \
 && rm -f /etc/apache2/sites-enabled/000-default.conf \
 && rm -f /etc/apache2/conf-enabled/docker-php.conf 2>/dev/null || true
COPY apache/vaultkeeper.conf /etc/apache2/sites-available/vaultkeeper.conf
RUN a2ensite vaultkeeper
COPY apache/php-vk.ini /usr/local/etc/php/conf.d/zz-vk.ini

COPY src/ /var/www/html/
COPY init.sql /docker-entrypoint-init.sql
COPY my.cnf /etc/mysql/conf.d/vaultkeeper.cnf
COPY entrypoint.sh /entrypoint.sh
COPY flag.txt /flag.txt

RUN mkdir -p /var/www/data /var/www/private \
 && chown -R www-data:www-data /var/www/html /var/www/data \
 && chmod 0644 /flag.txt \
 && chmod +x /entrypoint.sh

EXPOSE 80
CMD ["/entrypoint.sh"]
