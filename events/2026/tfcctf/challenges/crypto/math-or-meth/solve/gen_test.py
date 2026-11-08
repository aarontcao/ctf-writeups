import secrets, json
from Crypto.Util.number import getPrime, bytes_to_long
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))
msg = b'this_is_only_a_local_test_string_not_the_real_flag_abcd'
n = 57; B = 32; base = B+1
p = getPrime(1084)
x = bytes_to_long(msg)
row=[]
while x:
    row.append(x%base); x//=base
m=len(row)
print("m =", m)
a=[secrets.randbelow(p) for _ in range(n)]
A=[[secrets.randbelow(base) for _ in range(m)] for _ in range(n)]
pi=secrets.randbelow(n)
A[pi]=row[:]
h=[sum(a[i]*A[i][j] for i in range(n))%p for j in range(m)]
json.dump({"n":n,"m":m,"B":B,"p":p,"h":h,"row":row,"pi":pi,"A":A}, open(f"{_CH}/scratch/test.json","w"))
