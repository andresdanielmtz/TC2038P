def isPalindrome(word):
    l = 0
    r = len(word) - 1
    while r >= l:
        if word[r] != word[l]:
            return False
        l += 1
        r -= 1
    return True


word = "saippuakivikauppiaas"
res = isPalindrome(word)
print(res)