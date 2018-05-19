---
excerpt: Interview Cake Problem 24: Product of Other Numbers
mathjax: true
---

## Product of Other Numbers

---
*Difficulty: Easy*

---

In this problem we are given an array ```A``` of integers, and asked to return an array ```O``` of the same size in which ```O[i]``` contains the product of all elements in ```A``` *except* ```A[i]```.

**Naive Implementation**
The problem states that we must not use division, which is understandable because otherwise we could calculate the product once and then divide it by the value at each index to solve it -- in O(n) time and O(1) extra space.

Without division, a brute force implementation would be to calculate the product of all other numbers for each index, which would take $O(n^2)$ time.  

**Optimal Solution: Imperative**

**Optimal Solution: Functional**
