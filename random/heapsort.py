#!/usr/local/bin/python3

import heapq

def heapsort(arr, descending=False):
    h = []
    for val in arr:
        heapq.heappush(h, val)
    retarr = [heapq.heappop(h) for _ in range(len(h))]
    return retarr[::-1] if descending else retarr

arr = [8,7,2,1,5,3,8,1,6]
print(arr)
sorted_arr = heapsort(arr,descending=True)
print(sorted_arr)
