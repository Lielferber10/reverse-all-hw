allowed = [i for i in range(1,13)]
used = []
res = [0 for i in range(12)]

def validate(num):
    return (num in allowed) and (not (num in used))


for x7 in range(13):
    used = [x7]
    res[6] = x7

    for x9 in range(13):
        if x9 in used:
            continue
        used = [x7, x9]
        res[8] = x9
        
        for x10 in range(1,13):
            if x10 in used:
                continue
            used = [x7,x9,x10]
            res[9] = x10
            
            for x11 in range(1,13):
                if x11 in used:
                    continue
                used = [x7, x9, x10 ,x11]
                res[10] = x11
                
                for x12 in range(1,13):
                   if x12 in used:
                       continue
                   
                   used = [x7, x9, x10 ,x11, x12]
                   res[11] = x12

                   res[0] = -13 + x9 + x10
                   if not validate(res[0]):
                       continue
                   used.append(res[0])
                   
                   res[1] =-13 + x7 + x10
                   if not validate(res[1]):
                       continue
                   used.append(res[1])
                   
                   res[2] = -26 + x7 +x9 +x10 +x11 +x12
                   if not validate(res[2]):
                       continue
                   used.append(res[2])
                   
                   res[3] = 39-x7 -x9 -x10 -x11
                   if not validate(res[3]):
                       continue
                   used.append(res[3])
                   
                   res[4] = 26 - x7 -x10 -x12
                   if not validate(res[4]):
                       continue
                   used.append(res[4])
                   
                   res[5] = 39-x7-x9-x10-x12                   
                   if not validate(res[5]):
                       continue
                   used.append(res[5])
                   
                   res[7] = 26 - x9 -x10 -x11
                   if not validate(res[7]):
                       continue
                   used.append(res[7])
                   
                   eq1 = (res[1] + res[2] + res[3] + res[4])
                   eq2 = (res[7]+res[8]+res[9]+res[10])
                   eq3=(res[0]+res[2]+res[5]+res[7])
                   eq4 = (res[0]+res[3]+res[6]+res[10])
                   eq5=(res[1]+res[5]+res[8]+res[11])
                   eq6=(res[4]+res[6]+res[9]+res[11])
                   eq7=(res[0]+res[1]+res[4]+res[7]+res[10]+res[11])
                   if eq1== eq2 ==eq3 == eq4==eq5 == eq6 == eq7 == 26:
                       print(res)
                   
               
               