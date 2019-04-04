#! /usr/local/bin/python3

from numpy.random import shuffle

def partition(A, pivot_index):
    pivot = A[pivot_index]
    # Keep the following invariants during partitioning:
    # bottom group = [:smaller]
    # middle group = [smaller:equal]
    # unclassified group = [equal:larger]
    # top group = [larger:]
    smaller, equal, larger = 0, 0, len(A)
    # keep iterating as long as there is an unclassified element..
    while equal < larger:
        if A[equal] < pivot: # lt --> incrememnt bottom group
            A[smaller], A[equal] = A[equal], A[smaller]
            smaller, equal = smaller + 1, equal + 1
        elif A[equal] == pivot: # eq --> increment middle group
            A[smaller], A[equal] = A[equal], A[smaller]
            equal += 1
        elif A[equal] > pivot: # gt --> incrememnt top group
            larger -= 1
            A[equal], A[larger] = A[larger], A[equal]
    return 

def quicksort_helper(A, left, right):
    # Base case: an empty or unit-length array is sorted
    if right - left <= 1:
        return
    # Select pivot_index as midpoint of range (left, right]
    pivot_index = left + (right - left) // 2
    # Partition that range into 3 regions [{x: x < pivot},{y: y == pivot}, {z: z > pivot}]
    partition(A, pivot_index)
    # Sort the bottom and top regions from that partition
    quicksort_helper(A, left, pivot_index)
    quicksort_helper(A, pivot_index, right)

def quicksort(A):
    # Randomly suffle the input to ensure average-case runtime O(nlogn)
    shuffle(A)
    quicksort_helper(A, 0, len(A))

if __name__ == '__main__':
    import sys
    try:
        arr = list(map(int, sys.argv[1][1:-1].split(',')))
    except:
        exit("usage: ./quicksort.py [<comma separated array of integers>]")
    print("input:  {}".format(arr))
    quicksort(arr)
    print("sorted: {}".format(arr))