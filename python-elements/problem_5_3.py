#! /usr/local/bin/python3

"""
Problem: Mutiply two arbitrary-precision integers

Input:  Two integers with each digit stored in arrays
Output: Product as an array, with the 0th index having a signed digit

---

Algorithm: grade-school digit-by-digit multiplication
"""

def multiply(A, B):
    # determine sign of final result
    sign = -1 if (A[0] < 0) ^ (B[0] < 0) else 1
    # remove signs
    A[0], B[0] = abs(A[0]), abs(B[0])

    # max places in result is len(A) + len(B)
    result = [0] * (len(A) + len(B))
    # go backwards because least-sig digit of num is in arr[-1]
    for i in reversed(range(len(A))):
        for j in reversed(range(len(B))):
            # raw product
            result[i + j + 1] += A[i] * B[j]
            # carry propagated to next place
            result[i + j] += result[i + j + 1] // 10
            # product with carry removed
            result[i + j + 1] %= 10

    # remove leading zeros
    # - the 'next' piece keeps going until x[i] isn't 0, and returns i
    # - the [] or [0] piece ensures we return [0] and not an [] if the result is actually zero
    result = result[next((i for i, x in enumerate(result) if x != 0), len(result)):] or [0]
    # restore sign
    return [sign * result[0]] + result[1:]

a, b, exp = [1,9,3,7,0,7,7,2,1], [-7,6,1,8,3,8,2,5,7,2,8,7], [-1,4,7,5,7,3,9,5,2,5,8,9,6,7,6,4,1,2,9,2,7]
result = multiply(a.copy(), b.copy())
assert (result == exp), "result {} != expected {}".format(result, exp)
intify = lambda l: ''.join([str(x) for x in l])
print("{} x {} = {}".format(intify(a),intify(b),intify(result)))
