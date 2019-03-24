#!/usr/local/bin/python3

import sys

def make_change(total, coin_values):
    min_coins = [float('inf') for _ in range(0,total+1)]
    prev_min = [(-1, -1) for _ in range(0,total+1)]
    min_coins[0] = 0
    for i in range(1, total+1):
        for j in range(0, len(coin_values)):
            v_j = coin_values[j]
            if ( v_j <= i ) and ( min_coins[i - v_j] + 1 < min_coins[i] ):
                min_coins[i] = min_coins[i - v_j] + 1
                prev_min[i] = (i - v_j, v_j)
    k = total
    coins_used = []
    while prev_min[k][0] != -1:
        coins_used.append( prev_min[k][1] )
        k = prev_min[k][0]
    return min_coins[total], coins_used

try:
    value = int(sys.argv[1])
    coins = [int(coin) for coin in sys.argv[2].strip()[1:-1].split(',')]
except:
    exit("usage: ./make_change.py <value> [<c1>,<c2>,...,<cn>]")
print(make_change(value, coins))
