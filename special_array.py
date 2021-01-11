def specialArray( nums) -> int:
    # You are given an array nums of non-negative integers
    # nums is special if here is a number x such that there are 
    # x numbers in nums that are greater than or equal to x
    
    for i in range(max(nums)+1):
        counti = 0
        for j in nums:
            print('counti...', counti, i, j)
            if j >= i:
                counti += 1
        if counti > 0 and counti == i:
            return i
    return -1

print(specialArray([3,5]))
print(specialArray([0,0]))
print(specialArray([0,4,3,0,4]))
print(specialArray([3,6,7,7,0]))
print(specialArray([100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100]))