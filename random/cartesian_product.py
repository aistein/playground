#!/usr/local/bin/python3

import sys

def product_of_two(A, B):
    if len(A) == 0:
        return B
    if len(B) == 0:
        return A
    product = []
    for i in range(len(A)):
        for j in range(len(B)):
            product.append( [ A[i], B[j] ] )
    return product

def cartesian_product(groups):
    product = []
    for group in groups:
        product = product_of_two(product, group)
    return product

try:
    groups = []
    for group in sys.argv[1:]:
        groups.append([item for item in group.strip()[1:-1].split(',')])
except:
    exit("usage: ./cartesian_product.py [<item>,<item>,...,<item>] [<item>,...] ...")
    pass

print(groups)
print(len(cartesian_product(groups)))
