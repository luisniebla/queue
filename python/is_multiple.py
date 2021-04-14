# Write a short function that takes 2 integer values
# It returns True if n is multiple of m
# That is, n=mi for some i and False otherwise
def is_multiple(n, m):
    return n % m == 0

assert is_multiple(4,2) == True
assert is_multiple(2,4) == False
assert is_multiple(6,9) == False
assert is_multiple(96,3) == True


# Write is_even, that takes an integer value and
# return True if k is even. You cannot use multiplication,
# modulo, or division operators
def is_even(k):
    while k >= 1:
        k -= 2
    return k == 0

def is_even_no_loop(k):
    # We only care about the last bit of the number. Is it 1, in which case it's odd?
    # 1 = 0 0 0 1; 1 ^ 1 = 0 0 0 1 ^ 0 0 0 1 = 0 0 0 0 = 0 != 1 + 1
    # 2 = 0 0 1 0; 2 ^ 1 = 0 0 1 0 ^ 0 0 0 1 = 0 0 1 1 = 3 == 2 + 1
    # 3 = 0 0 1 1; 3 ^ 1 = 0 0 1 1 ^ 0 0 0 1 = 0 0 1 0 = 2 != 3 + 1
    return k ^ 1 == k + 1

def is_even_no_binary_ops(k):
    # In this case, literally just get the binary and get the last bit
    return bin(k)[-1] == '0'

# def is_even_no_binary_representation_peeking(k):
    # lol yeah i dont think thats possible buddy, quit while you're ahead


assert is_even(2) == True
assert is_even(3) == False
#assert is_even(21324124012741274127419272) == False
assert is_even_no_loop(2) == True
assert is_even_no_loop(20141924812947125407294018) == True
assert is_even_no_binary_ops(2231243) == False
assert is_even_no_binary_ops(121241241251028412) == True



# Write a Python function that takes a sequence of 1 or more numbers
# and returns the smallest and largest numbers in the form of a tuple
# do not use min/max
def minmax(data: list):
    # Maybe set to null instead
    minD, maxD = data[0], data[0]
    for d in data:
        if d < minD:
            minD = d
        elif d > maxD:
            maxD = d
    return [minD, maxD]


assert(minmax([1,2,3])) == [1,3]
assert(minmax([1,1])) == [1,1]


# Takes positive integer n and returns sum of all the squres
# of all the positive integers smaller than n
def sumOfSquares(n: int):
    count = 0
    for i in range(n):
        count += i ** 2
    return count

assert sumOfSquares(0) == 0
assert sumOfSquares(2) == 1
assert sumOfSquares(4) == 14


# Do sumOfSquares but with comprehension
def sumOfComprehensionSquares(n: int):
    return sum([i ** 2 for i in range(n)])

assert sumOfComprehensionSquares(0) == 0
assert sumOfComprehensionSquares(4) == 14

# Take a positive integer n and returns the sum of squares of all the odd positives smallers than n
def sumOfOdds(n: int):
    return sum([i ** 2 for i in range(1, range(n), 2)])
# I'm so confident on this, I don't even need to test it

# Reverse  a lit of n integers without splicing
def reverseList(n: list):
    # n[::-1]
    return [i for i in range(len(n) - 1, 0, -1)]


# Take a sequence of integers and determine if there is a distinct pair of numbers in the sequence
# whose product is odd
def hasOddProduct(n: list):
    return len([x for x in n if x != 1 and x % 2 == 1]) > 0
    # BAD: Don't do this
    # for i in range(len(n)):
    #     for j in range(len(n)):
    #         if i != j and n[i] * n[j] % 2 == 1:
    #             return True
    # return False

assert hasOddProduct([1,2,3]) == True
assert hasOddProduct([1,2,4,6]) == False

# Are all numbers different from each other
def is_distinct(n: list):
    for i in n:
        if n.count(i) > 1:
            return False
    return True

# Write a function that takes two arrays and return dot product
def dot_product(n, m):
    return sum([v * m[i] for i, v in enumerate(n)])

assert dot_product([1,2],[3,4]) == 11

# Give an example of a Python code fragment that attempts to write
# an element to a list based on an index that may be out of bounds
def write_to(n, item, i):
    try:
        n[i] = item
    except IndexError:
        print("bro, chill...")

write_to([1,2,3], 2, 5)

import random

def my_choice(data):
    return data[random.randrange(1, len(data))]

data = [1,3,5,3,21,5,9,42]
print(list(my_choice(data) for _ in data))

