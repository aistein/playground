################
# Question 2
################

"""
We have some clickstream data that we gathered on our client's website. Using cookies, we collected snippets of users' anonymized URL histories while they browsed the site. The histories are in chronological order and no URL was visited more than once per person.

Write a function that takes two users' browsing histories as input and returns the longest contiguous sequence of URLs that appears in both.

Sample input:

user0 = ["/start.html", "/pink.php", "/register.asp", "/orange.html", "/red.html"]
user1 = ["/start.html", "/green.html", "/blue.html", "/pink.php", "/register.asp", "/orange.html"]
user2 = ["/red.html", "/green.html", "/blue.html", "/pink.php", "/register.asp"]
user3 = ["/blue.html", "/logout.php"]

Sample output:

findContiguousHistory(user0, user1)
   /pink.php
   /register.asp
   /orange.html

findContiguousHistory(user1, user2)
   /green.html
   /blue.html
   /pink.php
   /register.asp

findContiguousHistory(user0, user3)
   (empty)

findContiguousHistory(user2, user3)
   /blue.html

findContiguousHistory(user3, user3)
   /blue.html
   /logout.php

"""
user0 = ["/superduper.html","/start.html", "/pink.php", "/register.asp", "/orange.html", "/red.html"]
user1 = ["/start.html", "/green.html", "/blue.html", "/pink.php", "/register.asp", "/orange.html"]
user2 = ["/red.html", "/green.html", "/blue.html", "/pink.php", "/register.asp"]
user3 = ["/blue.html", "/logout.php"]
user4 = ["/pink.php", "/register.asp", "/orange.html"]
user5 = []

import copy
def longest_common_sequence(usera, userb):
    curr_max_seq = []
    i, j = 0, 0
    while i < len(usera) and j < len(userb):
        curr_seq = []
        print("\n\n NEW LOOP")
        print("first: i {}, j {}".format(i,j))
        
        # find first common element
        for url in usera[i:]:
            if url in userb:
                print("first common element = {}".format(url))
                j += userb[j:].index(url)
                break
            i += 1
            
        print("second: i {}, j {}".format(i,j))
            
        print("here")
                        
        # if no common elements, break
        if i == len(usera) or j == -1:
            return curr_max_seq
        
        print(curr_seq)
        print(curr_max_seq)
        
        # increment in lockstep until no longer common
        print(usera[i])
        print(userb[j])
        while i < len(usera) and j < len(userb) and usera[i] == userb[j]:
            print("inside")
            curr_seq.append(usera[i])
            i, j = i+1, j+1
            
        print("third: i {}, j {}".format(i,j))
        print(curr_seq)
            
        # check if its the new max
        print(len(curr_seq))
        print(len(curr_max_seq))
        if len(curr_seq) > len(curr_max_seq):
            curr_max_seq = copy.deepcopy(curr_seq)
        
        # i, j = i+1, j+1
        
    return curr_max_seq
    
print(longest_common_sequence(user3, user3))

############
# Question 1:
############

# counts = [ "900,google.com",
#      "60,mail.yahoo.com",
#      "10,mobile.sports.yahoo.com",
#      "40,sports.yahoo.com",
#      "300,yahoo.com",
#      "10,stackoverflow.com",
#      "2,en.wikipedia.org",
#      "1,es.wikipedia.org",
#      "1,mobile.sports",
#      "1,google.co.uk"]

# from collections import defaultdict
# def advertising_stats(counts):
#     domain_stats = defaultdict(int)
#     for entry in counts:
#         count, url = entry.split(",")
#         count = int(count)
#         domains = url.split(".")
#         curr = ""
#         for domain in reversed(domains):
#             curr = domain + '.' + curr
#             domain_stats[curr[:-1]] += count
#     return domain_stats
    
# [print(count) for count in advertising_stats(counts).items()]
        




















