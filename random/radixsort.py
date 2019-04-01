#!/usr/local/bin/python3

from collections import defaultdict

def radix_sort(arr, digits):
    """
    arr: list(int)  - list to be sorted
    digits: int     - the maximum number of digits for any elemnt of arr
    """
    # range from least significant digit to most significant
    for place in range(digits):
        #print(arr)
        by_digit = defaultdict(list)
        # 'counting-sort' each element into a digit-indexed dict
        for elem in arr:
            digit = (elem // 10**place) % 10
            by_digit[digit].append(elem)
        # reorganize array according to csort on this place
        arr_pos = 0
        for i in range(10):
            for elem in by_digit[i]:
                arr[arr_pos] = elem
                arr_pos += 1

if __name__ == '__main__':
    arr = [2, 101, 8, 11, 52, 36, 189, 1, 1000, 1238, 4328, 22, 258, 1, 5, 9837]
    print(arr)
    radix_sort(arr, 4)
    print(arr)

