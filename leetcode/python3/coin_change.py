#!/usr/local/bin/python3
import unittest
from collections import deque

# recursive solution
def coinChange(coins, amount):
    memo = {}
    return coinChangeHelper(memo, coins, amount)
def coinChangeHelper(memo, coins, amount):
    if amount == 0:
        memo[amount] = 0
        return 0
    curr_min = float('inf')
    for c in coins:
        if (amount - c) >= 0:
            if (amount - c) in memo:
                s = memo[amount-c]
            else:
                s = coinChangeHelper(memo, coins, amount-c)
            if s >= 0:
                curr_min = min(curr_min, s + 1)
    memo[amount] = -1 if curr_min == float('inf') else curr_min
    return memo[amount]

# iterative solution
def coinChangeIt(coins, amount):
    DP = {0:0}
    for i in range(1, amount + 1):
        curr_min = float('inf')
        for c in coins:
            if i-c >= 0:
                curr_min = min(curr_min, 1 + DP[i - c]) if (i - c) in DP else float('inf')
        DP[i] = curr_min
    return -1 if DP[amount] == float('inf') else DP[amount]

# graph-theoretic solution
def coinChangeGT(coins, amount):
    q = deque([0, None])
    explored = set()
    depth = 0
    while(len(q) > 0):
        print("queue contents: {}".format(q))
        s = q.popleft()
        if s == amount:
            return depth
        if s == None:
            depth += 1
            q.append(None)
            if q[1] == None:
                return -1
            continue
        print("popped {}, currdepth {}".format(s, depth))
        for c in coins:
            if (s + c) in explored or (s + c) in q:
                continue
            q.append(s + c)
        explored.add(s)
    return -1


class TestCoinChange(unittest.TestCase):
    def test_simple(self):
        inp = ([1,3,5], 11)
        exp = [3]
        self.assertIn(coinChange(*inp), exp, "Expected:{}".format(exp))
        self.assertIn(coinChangeIt(*inp), exp, "Expected:{}".format(exp))
        self.assertIn(coinChangeGT(*inp), exp, "Expected:{}".format(exp))
    def test_short(self):
        inp = ([2], 3)
        exp = [-1]
        self.assertIn(coinChange(*inp), exp, "Expected:{}".format(exp))
        self.assertIn(coinChangeIt(*inp), exp, "Expected:{}".format(exp))
        self.assertIn(coinChangeGT(*inp), exp, "Expected:{}".format(exp))
    def test_long(self):
        inp = ([1,2,5], 100)
        exp = [20]
        self.assertIn(coinChange(*inp), exp, "Expected:{}".format(exp))
        self.assertIn(coinChangeIt(*inp), exp, "Expected:{}".format(exp))
        self.assertIn(coinChangeGT(*inp), exp, "Expected:{}".format(exp))

if __name__ == '__main__':
    unittest.main()
