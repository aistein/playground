#!/usr/local/bin/python3

def merge(left,right):
    m = []
    l, r, = 0, 0
    while l < len(left) and r < len(right):
        if left[l] < right[r]:
            m.append(left[l])
            l += 1
        else:
            m.append(right[r])
            r += 1
    if l < len(left):
        m.extend(left[l:])
    if r < len(right):
        m.extend(right[r:])
    return m

def mergesort(arr):
    if len(arr) == 1:
        return arr
    if len(arr) == 2:
        return [min(arr), max(arr)]
    left = mergesort(arr[:len(arr)//2])
    right = mergesort(arr[len(arr)//2:])
    return merge(left,right)

arr = [1,8,7,4,3,4,9,0,11,4,13,5,6]
print(arr)
print(mergesort(arr))
