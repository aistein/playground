#!/usr/local/bin/python3

import unittest

def longestPalindrome(s):

    # validity check
    N = len(s)
    if N <= 1:
        return s

    # initial conditions for tracking backwards
    dp_star = 1
    i_star, j_star = N-1, N-1
    P = [True if k == N-1 else False for k in range(N)]

    # In the 2-D version, P[i][j] depends only on P[i+1][j-1].
    # Make P 1-D by letting P[0..N] represent the i+1th row (iterate rows downwards)
    # This also requires traversing P backwards in the inner loop, so that ...
    # ... the j-1th entry from the previous round is always available.
    # Traverse 1 row at a time in outer loop, hitting all columns in inner loop
    for i in range(N-1, -1, -1):
        for j in range(N-1, -1, -1):
            if  (j == i) or ((j == i+1 or P[j-1]) and s[i] == s[j]):
                # print("s[{}:{}] = {}".format(i,j+1, s[i:j+1]))
                P[j] = True
                if (j-i+1) > dp_star:
                    dp_star = (j-i+1)
                    i_star, j_star = i, j
            else:
                P[j] = False

    return s[i_star:j_star+1]

class TestLongestPalindrome(unittest.TestCase):
    def test_empty(self):
        inp = ""
        exp = [""]
        self.assertIn(longestPalindrome(inp), exp, "Expected:{}".format(exp))
    def test_simple(self):
        inp = "cbbd"
        exp = ["bb"]
        self.assertIn(longestPalindrome(inp), exp, "Expected:{}".format(exp))
    def test_short(self):
        inp = "aa"
        exp = ["aa"]
        self.assertIn(longestPalindrome(inp), exp, "Expected:{}".format(exp))
    def test_long(self):
        inp = "abracadabra"
        exp = ["aca", "ada"]
        self.assertIn(longestPalindrome(inp), exp, "Expected:{}".format(exp))
    def test_many(self):
        inp = "abcba121dadeeefgfeee"
        exp = ["eeefgfeee"]
        self.assertIn(longestPalindrome(inp), exp, "Expected:{}".format(exp))

if __name__ == '__main__':
    unittest.main()
