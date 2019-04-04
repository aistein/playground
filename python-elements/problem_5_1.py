#! /usr/local/bin/python3

"""
Problem: Dutch National Flag

Write a program that takes an array A and an index i into A, and rearranges the
elements such that all elements less than A[i] (the "pivot") appear first,
followed by elements equal to the pivot, followed by elements greater than the
pivot.
"""

def dnf_part_naive(A, pivot_index):
    """
    O(n) time and O(n) space
    """
    pivot = A[pivot_index]
    lt, eq, gt = [], [], []
    for elem in A:
        if elem > pivot:
            gt.append(elem)
        elif elem == pivot:
            eq.append(elem)
        else:
            lt.append(elem)
    return lt + eq + gt

def dnf_part_opt1(A, pivot_index):
    """
    O(n^2) time and O(1) space
    """
    pivot = A[pivot_index]
    # pass 1: get values less than pivot
    for i in range(len(arr)):
        for j in range(i+1,len(arr)):
            if A[j] < pivot:
                A[i], A[j] = A[j], A[i]
                break
    # pass 2: get values greater than pivot
    for i in reversed(range(len(arr))):
        if A[i] < pivot:
            break
        for j in reversed(range(i)):
            if A[j] > pivot:
                A[i], A[j] = A[j], A[i]
                break
    return A

def dnf_part_opt2(A, pivot_index):
    """
    O(n) time and O(1) space - two passes
    """
    pivot = A[pivot_index]
    # pass 1: get values less than pivot
    smaller = 0
    for i in range(len(A)):
        if A[i] < pivot:
            A[i], A[smaller] = A[smaller], A[i]
            smaller += 1
    # pass 2: get values larger than pivot
    larger = len(A) - 1
    for i in reversed(range(len(A))):
        if A[i] < pivot:
            break
        if A[i] > pivot:
            A[i], A[larger] = A[larger], A[i]
            larger -= 1
    return A

def dnf_part_opt3(A, pivot_index):
    """
    O(n) time and O(1) space - one pass
    """
    pivot = A[pivot_index]
    # Keep the following invariants during partitioning:
    # bottom group: A[:smaller]
    # middle group: A[smaller:equal]
    # unclassified group: A[equal:larger]
    # top group: A[larger:]
    smaller, equal, larger = 0, 0, len(A)
    while equal < larger:
        if A[equal] < pivot: # lt --> incrememnt bottom group
            A[smaller], A[equal] = A[equal], A[smaller]
            smaller, equal = smaller + 1, equal + 1
        elif A[equal] == pivot: # eq --> incrememnt middle group
            A[smaller], A[equal] = A[equal], A[smaller]
            equal += 1
        elif A[equal] > pivot: # gt --> incrememnt top group
            larger -= 1
            A[larger], A[equal] = A[equal], A[larger]
    return A


arr = [0,1,2,0,2,1,1]
pivot_index = 3
print(arr)
print(dnf_part_naive(arr, pivot_index))
print(dnf_part_opt1(arr.copy(), pivot_index))
print(dnf_part_opt2(arr.copy(), pivot_index))
print(dnf_part_opt3(arr.copy(), pivot_index))