import binascii
f = open ("123.txt","r")
nf = open("123.jpg","wb")
while 1:
    c = f.readline()
    d = c.strip()
    if not c:
        break
    nf.write(binascii.a2b_hex(bytes(d, "ascii")))
f.close()
nf.close()
