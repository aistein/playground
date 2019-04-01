#!/usr/local/bin/python3

import math
if __name__ == '__main__':
    n = int(input())
    # error cases - print nothing
    if n <= 0:
        print('')
    else:
        # first, calculate the number of digits that will be in output
        digits_in_output = 0
        rank = 1
        while 10**(rank) <= n:
            digits_in_output += (10**(rank) - 10**(rank-1)) * rank
            rank += 1
            print("d_i_o = {}".format(digits_in_output))
            print("rank = {}".format(rank))
        digits_in_output += (n-10**(rank-1)) * rank + rank
        print("digits_in_output = {}".format(digits_in_output))
        # second, calculate the output
        o = 0
        output_position = digits_in_output - 1
        for i in range(n):
            digits_in_i = int(math.floor(math.log10(i+1))) + 1
            rem = i+1 # want output to start at 1, not 0
            for j in range(digits_in_i):
                position_within_i = digits_in_i - j - 1
                o += 10**(output_position)*(rem//10**(position_within_i))
                rem %= 10**(position_within_i)
                output_position -= 1
        print(o)
