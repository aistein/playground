#!/usr/local/bin/python3

import time

#def wordBreak(s, wordDict):
#    n = len(s)
#    dp = [ False for i in range(n+1) ]
#    dp[0] = True
#    for i in range(1, n+1):
#        for j in range(0, i):
#            if dp[j] and (s[j:i] in wordDict):
#                dp[i] = True
#                break
#    return dp[-1]

#def wordBreak(s, wordDict):
#    n = len(s)
#    dp = [0] # optimization: avoid having O(n) array, only care about True dp indices
#    for i in range(1, n+1):
#        for j in dp:
#            if (j < i):
#                if s[j:i] in wordDict:
#                    dp.append(i)
#                    break
#    return (dp[-1] == n)

def wordBreak(s, wordDict):
    n = len(s)
    dp = [0] # optimization: avoid having O(n) array, only care about True dp indices
    for i in range(1, n+1):
        for j in dp:
            if s[j:i] in wordDict:
                dp.append(i)
                break
    return (dp[-1] == n)

s = "leetcode"
wordDict = ["leet","code"]
print("Test 1: s = {}, wordDict = {}".format(s, wordDict))
try:
    start = time.time()
    assert wordBreak(s, wordDict) == True, "Test 1 Failed!"
    print("...completed in {} s.".format(time.time() - start))
except AssertionError as error:
    exit(error)

s = "applepenapple"
wordDict = ["apple","pen"]
print("Test 2: s = {}, wordDict = {}".format(s, wordDict))
try:
    start = time.time()
    assert wordBreak(s, wordDict) == True, "Test 2 Failed!"
    print("...completed in {} s.".format(time.time() - start))
except AssertionError as error:
    exit(error)

s = "catsandog"
wordDict = ["cats","dog","sand","and","cat"]
print("Test 3: s = {}, wordDict = {}".format(s, wordDict))
try:
    start = time.time()
    assert wordBreak(s, wordDict) == False, "Test 3 Failed!"
    print("...completed in {} s.".format(time.time() - start))
except AssertionError as error:
    exit(error)
