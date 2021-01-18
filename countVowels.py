def countMe(n, last_character):
    if n == 1:
        return 1
    lexi = ['a', 'e', 'i', 'o', 'u']
    count = 0
    for l in lexi:
        if last_character <= l:
            count += countMe(n-1, l)
    return count
def countVowelStrings( n: int) -> int:
    lexi = ['a', 'e', 'i', 'o', 'u']
    count = 0
    for l in lexi:
        count += countMe(n, l)
    return count

print(countVowelStrings(1))
print(countVowelStrings(2))
print(countVowelStrings(33))
print(countVowelStrings(42))