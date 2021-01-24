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
