#!/usr/local/bin/python3

def remove_dup(arr):
    last_unique_val = arr[0]
    pivot = 1
    for i in range(1, len(arr)):
        if arr[i] != last_unique_val:
            if pivot != i:
                arr[pivot], arr[i] = arr[i], arr[pivot]
            last_unique_val = arr[pivot]
            pivot += 1
    return pivot

# Base Test
arr = [2, 3, 5, 5, 7, 11, 11, 11, 13]
exp = [2, 3, 5, 7, 11, 13]
print("Running Base test...\narr = {}\nexp = {}".format(arr, exp))
k = remove_dup(arr)
print("Result:\nk = {}\narr = {}".format(k, arr))
assert (k == 6) and (arr[:k] == exp), "Failed base test."
print("Passed base test.")

# No Duplicates
arr = [2, 3, 4, 5, 7, 9, 11, 12, 13]
exp = [2, 3, 4, 5, 7, 9, 11, 12, 13]
print("Running no duplicates test...\narr = {}\nexp = {}".format(arr, exp))
k = remove_dup(arr)
print("Result:\nk = {}\narr = {}".format(k, arr))
assert (k == 9) and (arr[:k] == exp), "Failed no duplicates test."
print("Passed no duplicates test.")

# All Duplicates
arr = [1, 1, 1, 1]
exp = [1]
print("Running all duplcates test...\narr = {}\nexp = {}".format(arr, exp))
k = remove_dup(arr)
print("Result:\nk = {}\narr = {}".format(k, arr))
assert (k == 1) and (arr[:k] == exp), "Failed all duplicates test."
print("Passed all duplicates test.")

# Long Array
arr = [(i-1) if i%10 == 0 else i for i in range(1,1000)]
exp = []
for i in range (1, 1000):
    if i%10 != 0:
        exp.append(i)
#print("Running long array test...")
k = remove_dup(arr)
print("Result:\nk = {}".format(k))
assert arr[:k] == exp, "Failed long array test."
print("Passed long array test.")
