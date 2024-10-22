lst = [1,2,3,4,5,6,6,7,8,9]
dic = {} 

for elem in lst: 
    if elem in dic:
        dic[elem] += 1
        print(elem) 
    else: 
        dic[elem] = 0
print(dic)

