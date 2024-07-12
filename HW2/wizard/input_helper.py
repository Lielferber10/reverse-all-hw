expected = 'CEFKOIAMMBLAICBDEMDEBNGNFBCK'
print(len(expected))
expected = expected[::-1]
res = 'I'

for i in range(1,len(expected)):
    c1 = ord(res[-1]) - 0x41
    c2 = ord(expected[i]) - 0x41
    res += str(chr((c1^c2)+0x41))

res = res[::-1]

for i in range(16):
    res += str('0')

print(res)