arr = [] 
local = []
for i in range(1, 16):
    if (i / 4).is_integer() and i > 0:
        arr.append(local)
        local = [] 
    else: 
        local.append(i)
print(arr)
    