#! /usr/local/bin/python3

import random

levels = 0

def nlogn_median(L):
    s = sorted(L)
    if len(L) % 2 == 1:
        return s[len(L)//2]
    return 0.5 * (s[len(L)//2 - 1] + s[len(L)//2])

def chunked(L, chunk_size):
    return [L[i:i+chunk_size] for i in range(0,len(L),chunk_size)]

def quickselect(L, k, pivot_fn=random.choice):
    pivot = pivot_fn(L)

    lows = [el for el in L if el < pivot]
    highs = [el for el in L if el > pivot]
    pivots = [el for el in L if el == pivot]

    if k < len(lows):
        return quickselect(lows, k, pivot_fn)
    elif k < len(lows) + len(pivots):
        return pivots[0]
    else:
        return quickselect(highs, k - len(lows) - len(pivots), pivot_fn)

def quickselect_median(L, pivot_fn=random.choice):
    globals()['levels'] += 1
    if len(L) % 2 == 1:
        return quickselect(L, len(L)//2, pivot_fn)
    return 0.5 * (quickselect(L, len(L)//2 - 1, pivot_fn) + quickselect(L, len(L)//2, pivot_fn))

def pick_pivot(L):
    if len(L) < 5:
        return nlogn_median(L)

    sorted_chunks = filter(lambda c : len(c) == 5, [sorted(chunk) for chunk in chunked(L,5)])
    medians = [chunk[2] for chunk in sorted_chunks]
    median_of_medians = quickselect_median(medians, pick_pivot)

    return median_of_medians

find_median = lambda l : quickselect_median(l, pick_pivot)

if __name__ == '__main__':

    #L = [1,2,4,3,9,11,56,43,2,5,5,5,5,0,9,8,1,3,1,3,2,2,2,4,8,8,99,23,143,8,11,13,5,7,7,7,7,8,6,5,4,3,4,3,4,5,2,6,6,66,7,77,88,99,99,99,100,1034,203,5,4324,4343,256,243,4,5,2,2,343432341]
    #print("L: {}".format(L))
    L = random.sample(range(1000000), 10000)
    print("len(L) = {}, median(L) = {}".format(len(L), find_median(L)))
    print("recursion depth = {}".format(globals()['levels']))



