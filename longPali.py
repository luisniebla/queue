def isPali(s):
    if s[::-1][1:] == s[1:]:
        return True


def longestPalindrome(s):
    # xabay
    # xabax
    maxLen = 0
    for i in range(len(s)):
        print('i -', i)
        for j in range(i, len(s)+1):
            print('checking', s[i:j])
            if isPali(s[i:j]) and j-i > maxLen:
                print('PALINDROME')
                maxLen = j-i
                
    return maxLen

print(longestPalindrome('cbbd'))