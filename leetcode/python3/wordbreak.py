#!/usr/local/bin/python3

def wordBreak(s, wordDict):
    n = len(s)
    dp = [ False for i in range(n+1) ]
    dp[0] = True
    for i in range(1, n+1):
        print("i = {}".format(i))
        for j in range(0, i):
            print("\tj = {}".format(j))
            print("\t\tdp[{}] = {}, s[{}:{}] = {}".format(j,dp[j],j,i,s[j:i]))
            if dp[j] and (s[j:i] in wordDict):
                print("\t\t\tCheck!")
                dp[i] = True
                break
    return dp[-1]

s = "leetcode"
wordDict = ["leet","code"]
print("Test 1: s = {}, wordDict = {}".format(s, wordDict))
try:
    assert wordBreak(s, wordDict) == True, "Test 1 Failed!"
except AssertionError as error:
    exit(error)

s = "applepenapple"
wordDict = ["apple","pen"]
print("Test 2: s = {}, wordDict = {}".format(s, wordDict))
try:
    assert wordBreak(s, wordDict) == True, "Test 2 Failed!"
except AssertionError as error:
    exit(error)

s = "catsandog"
wordDict = ["cats","dog","sand","and","cat"]
print("Test 3: s = {}, wordDict = {}".format(s, wordDict))
try:
    assert wordBreak(s, wordDict) == False, "Test 3 Failed!"
except AssertionError as error:
    exit(error)
