arr = [1, 7, 5, 9, 2, 12, 3]
k = 2


def pairs(arr, k):
    values = {}
    res = []
    for num in arr:
        values[num] = num
        if num + k in values:
            res.append((num + k, num))
        if num - k in values:
            res.append((num - k, num))

    return res


result = pairs(arr, k)
print(result)
