import sys, itertools
if(len(sys.argv) != 3):
    print("Usage: [FILE] [KEY]")
    exit(-1)

filename = sys.argv[1]
key = sys.argv[2]

with open(filename, 'rb') as plaintext:
    raw = plaintext.read()
    print(len(raw))
    with open(filename + '.out', 'wb') as ciphertext:
        for l, r in zip(raw, itertools.cycle(key)):
            ciphertext.write( (l ^ ord(r)).to_bytes(1, byteorder='big') )
