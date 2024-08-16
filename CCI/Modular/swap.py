def swap(arr) -> None:
    minIndex, highIndex = 0, 0
    for i in range(0, len(arr) - 1):
        if arr[i] < arr[minIndex]:
            minIndex = i
    for j in range(0, len(arr) - 1):
        if arr[j] > arr[highIndex]:
            highIndex = i 

    tmp = arr[minIndex]
    arr[minIndex] = arr[highIndex]
    arr[highIndex] = tmp 

def swap_opt(arr) -> None: 
    highIndex = minIndex = 0
    highVal = minVal = 0 

    for i in range(len(arr) - 1): 
        if arr[i] < minVal:
            minVal = arr[i] 
            minIndex = i 
        if arr[i] > highVal:
            highVal = arr[i]
            highIndex = i 

    tmp = arr[minIndex]
    arr[minIndex] = arr[highIndex]
    arr[highIndex] = tmp 


arr = [1, 5, 3, 20, 2]
swap_opt(arr)
print(arr)
