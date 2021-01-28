

# Write a short python fucntion that takes
# a sequence of integer values and determines if there
# if there is a distinct pair of numebrs in sequence whose
# product is odd
def is_distinct_pairs(n):
    for i, k in enumerate(n):
        for j, q in enumerate(n):
            if i != j:
                if k * q % 2 == 1:
                    return True
    return False

print(is_distinct_pairs([1,2,3]))
print(is_distinct_pairs([1,2]))


# Take a sequence of numbers and determines if all the numbers
# are different from each other
def is_distinct(n):
    while n:
        popped = n.pop()
        if popped in n:
            return False
    return True

print(is_distinct([1,2,3]))
print(is_distinct([1,2,2,3]))


ord_a = ord('a')
ord_z = ord('z')
print([chr(c) for c in range(ord_a,ord_z + 1, 1)])
# print('Comprehension', [i for i in range(0,90,2**i)])
