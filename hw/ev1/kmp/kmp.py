# Algorithm taken directly from 
# https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/

def computeLPSArray(pat):
    M = len(pat)
    lps = [0] * M

    # Length of the previous longest prefix suffix
    length = 0
    i = 1

    # Loop calculates lps[i] for i = 1 to M-1
    while i < M:
        if pat[i] == pat[length]:
            length += 1
            lps[i] = length
            i += 1
        else:
            if length != 0:
                length = lps[length - 1]
            else:
                lps[i] = 0
                i += 1
    return lps


def KMPSearch(pat, txt):
    M = len(pat)
    N = len(txt)

    # Create lps[] that will hold the longest prefix
    # suffix values for pattern
    lps = computeLPSArray(pat)
    result = []

    i = 0  # index for txt
    j = 0  # index for pat
    while (N - i) >= (M - j):
        if pat[j] == txt[i]:
            j += 1
            i += 1

        if j == M:
            result.append(i - j + 1)
            j = lps[j - 1]
        elif i < N and pat[j] != txt[i]:
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1
    return result


# Driver code
txt = "geeksforgeeks"
pat = "geeks"
result = KMPSearch(pat, txt)

# Print all the occurrences (1-based indices)
for index in result:
    print(index, end=" ")
