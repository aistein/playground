#!/usr/local/bin/python3

# Wrie a program that takes a 64-bit word and returns the 64-bit word
# consisting of the bits of the input word in reverse order. For example, if the
# input is (1110000000000001), the output should be (1000000000000111).

# pre-compute 16-bit reverse lookup table
HALFWORD_SIZE = 16

def swap_bits(halfword, a, b):
    a_mask = 0b1 << a
    b_mask = 0b1 << b
    # are the bits the same? If so, swapping has no effect
    if (halfword & a_mask) >> a != (halfword & b_mask) >> b:
        # if the bits are not the same, swapping them is the same as flipping them
        # ... we can use XOR to do this since a ^ 1 = ~a
        halfword ^= (a_mask | b_mask)
    return halfword

def reverse_halfword(halfword):
    for i in range(HALFWORD_SIZE//2):
        halfword = swap_bits(halfword, i, HALFWORD_SIZE-i)
    return halfword

lookup_reverse = {}
for halfword in range(pow(2,HALFWORD_SIZE)):
    lookup_reverse[halfword] = reverse_halfword(halfword)

# efficient function that makes use of precomputed hash-table (64-bit integer)
def reverse_uint64(num):
    HALFWORD_MASK = 0xffff
    return lookup_reverse[(num >> (0 * HALFWORD_SIZE)) & HALFWORD_MASK] << (3 * HALFWORD_SIZE) |\
           lookup_reverse[(num >> (1 * HALFWORD_SIZE)) & HALFWORD_MASK] << (2 * HALFWORD_SIZE) |\
           lookup_reverse[(num >> (2 * HALFWORD_SIZE)) & HALFWORD_MASK] << (1 * HALFWORD_SIZE) |\
           lookup_reverse[(num >> (3 * HALFWORD_SIZE)) & HALFWORD_MASK] << (0 * HALFWORD_SIZE)

num = 0x121c6d1595509082
print(hex(num))
print(hex(reverse_uint64(num)))
