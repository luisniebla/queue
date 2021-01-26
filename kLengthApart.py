
def kLengthApart(nums: int, k: int) -> bool:
    count = 0
    prevI = -1
    for i, n in enumerate(nums):
        print('True', i, prevI, k)
        if n == 1 and prevI == -1:
            prevI = i
        elif n == 1 and i - prevI <= k:
            print('False', n, i, prevI, k)
            return False
        elif n == 1:
            prevI = i
    return True

print(kLengthApart([1,0,0,1,0,1], 2))
print(kLengthApart([0,1,0,1], 1))
print(kLengthApart([1,1,1,1,1], 0))