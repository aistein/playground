#!/usr/local/bin/python3

def make_change(sum, coin_values):
    min_coins = [float('inf') for _ in range(0,sum+1)]
    prev_min = [(-1, -1) for _ in range(0,sum+1)]
    min_coins[0] = 0
    for i in range(1, sum+1):
        for j in range(0, len(coin_values)):
            v_j = coin_values[j]
            if ( v_j <= i ) and ( min_coins[i - v_j] + 1 < min_coins[i] ):
                min_coins[i] = min_coins[i - v_j] + 1
                prev_min[i] = (i - v_j, v_j)
    k = sum
    coins_used = []
    while prev_min[k][0] != -1:
        coins_used.append( prev_min[k][1] )
        k = prev_min[k][0]
    return min_coins[sum], coins_used