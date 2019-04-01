#!/usr/local/bin/python3

def counting_sort(arr, rng):
    if rng > len(arr)**2:
        raise OverflowError("range {} >> number of elements {}; don't use csort".format(
            rng,len(arr)))
    counts = [0 for _ in range(rng+1)]
    for num in arr:
        if num < 0:
            raise ValueError("{} not in valid range 0:{}".format(num, rng))
        counts[num] += 1
    for i in range(1, rng+1):
        counts[i] += counts[i-1]
    retarr = [0 for _ in range(len(arr))]
    for i in range(len(arr)):
        retarr[counts[arr[i]]-1] = arr[i]
        counts[arr[i]] -= 1
    return retarr

#arr = [1,8,7,5,3,4,8,6,5,1,2,4,5,13,8,11,9]
#print("input:  {}".format(arr))
#print("output: {}".format(counting_sort(arr)))
