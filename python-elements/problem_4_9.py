#!/usr/local/bin/python3

"""
Given an integer, return True if its string representation is a palindrome
(extension: what if the input could be an integer or a float)
"""

import sys
import numpy as np

def is_decimal_palindrome(d):
    # negative numbers cannot be palindromes
    if d < 0:
        return False
    num_digits = int(np.floor(np.log10(d))) + 1
    msd_mask = 10**(num_digits-1)
    # most significant digit is d/mask; least is d%10
    for i in range(num_digits // 2):
        if d // msd_mask != d % 10:
            return False
        d %= msd_mask      # remove MSD
        d //= 10           # remove LSD
        msd_mask //= 100   # chop off two mask digits
    return True

if len(sys.argv) > 0:
    print(is_decimal_palindrome(int(sys.argv[1])))
