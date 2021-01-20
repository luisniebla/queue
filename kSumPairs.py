# You are given an integer array nums and an integer k.

# In one operation, you can pick two numbers from the array
# whose sum equals k and remove them from the array.

# Return the maximum number of operations you can perform on the array.

def kSum(nums, k):
    # Idea: Sort the array
    # Start from the beginning, pick a number, and then proceed through array until you get a match
    q = []

    dynamicA = {}
    
    for n in nums:
        dynamicA.setdefault(n, {})
        for q in nums:
            dynamicA[n][q] = n + q
    newArr = []
    
    count = 0
    found = True
    while found:
        found = False
        print(i, n)
        pair = k - n
        if pair in nums and nums.index(pair) != i:
            nums.remove(n)
            nums.remove(pair)
            count += 1
            found = True
    return count

print(kSum([1,2,3,4], 5))
print(kSum([3,1,3,4,3], 6))
