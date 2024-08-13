arr1 = [13, 27, 35, 40, 49, 55, 59]
arr2 = [17, 35, 39, 40, 55, 58, 60]

def bcr(arr1, arr2) -> int:
    counter = 0
    elems = {}
    for num in arr1: 
        elems[num] = 0 # just initialize it 
    for num in arr2: 
        if num in elems:
            counter += 1 
    return counter

res = bcr(arr1, arr2)
print(res)

def bcr_linear(arr1, arr2) -> int: 
    counter = 0
    i, j = 0, 0
    
    while i < len(arr1) and j < len(arr2):
        if arr1[i] == arr2[j]: 
            counter += 1
            i += 1
            j += 1
        elif arr1[i] < arr2[j]:
            i += 1
        else:
            j += 1
    return counter

result = bcr_linear(arr1, arr2)
print(f"The result of linear is {result}")
