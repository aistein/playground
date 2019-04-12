#! /usr/local/bin/python3

def bestTrade(prices, start, end, loss):

    if start >= end:
        return 0, 0, 0

    running_min = end - 1 if loss else start
    curr_buy, curr_sell, curr_profit = (end-1, end-1, 0) if loss else (start, start, 0)
    ordered_indices = reversed(range(start,end)) if loss else range(start,end)

    for i in ordered_indices:
        if prices[i] < prices[running_min]:
            running_min = i
        elif prices[i] - prices[running_min] > curr_profit:
            curr_profit = prices[i] - prices[running_min]
            curr_buy, curr_sell = (i, running_min) if loss else (running_min, i)

    return curr_buy, curr_sell, curr_profit


def maxProfit(prices):

    n  = len(prices)
    if n < 2:
        return 0

    best_buy, best_sell, base_profit = bestTrade(prices, 0, n, False)
    _,_,profit_before = bestTrade(prices, 0, best_buy, False)
    _,_,profit_after = bestTrade(prices, best_sell+1, n, False)
    _,_,running_loss = bestTrade(prices, best_buy, best_sell+1, True)

    return base_profit + max(profit_before, profit_after, running_loss)

if __name__ == '__main__':
    """
    Find maximum profit possible with two trades or fewer
    """
    test_vectors = [
            [],
            [1],
            [1,2],
            [4,3,2],
            [1,2,3,4,5],
            [3,3,5,0,0,3,1,4],
            [6,3,1,2,4,7],
            [19,30,10,20,0,1,0,3,0,4],
            [1,4,5,0,2,10,3,11,1,0,1]
        ]
    for prices in test_vectors:
        print("prices: {}\n  profit: {}".format(prices, maxProfit(prices)))
