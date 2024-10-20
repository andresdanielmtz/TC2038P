# Kadane Algorithm 
## Used for maximum subarray sum

def maxSubarray(arr): 
    res = arr[0]
  
    for i in range(len(arr)):
        currSum = 0
      
        for j in range(i, len(arr)):
            print(f"i: {j} \t j: {j}")
            
            currSum = currSum + arr[j]
          
            # Update res if currSum is greater than res
            res = max(res, currSum)
          
    return res

example_array = [1,2,6,3,2,-100,10,10,10]
result = maxSubarray(example_array)
print(result) 
