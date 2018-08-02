#include <iostream>
#include <vector>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

// DP Solution running in O(n), with O(1) space
int fib_DP(int n)
{
    // compute the nth Fibonacci number
    if (n < 0)
        throw invalid_argument("n must be >= 0");

    if ( n == 1 || n == 0 )
        return n;

    int n1 = 1;
    int n2 = 0;
    int acc = n1 + n2;
    for (int i = 0; i < n-2; i++) {
        n2 = n1;
        n1 = acc;
        acc = n1 + n2;
    }
    return acc;
}

// Matrix Multiplication solution O(logn) time and O(logn) space because of
// recursive call-stack
// -- This works because the following identity has been proven
//	[ 1 1 ]^n    [ F^(n+1) F^(n)  ]
//  [ 1 0 ]   =  [ F^(n)   F^(n-1)]
void multiply(int F[2][2], int M[2][2]) {
	int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
	int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
	int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
	int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

	F[0][0] = x;
	F[0][1] = y;
	F[1][0] = z;
	F[1][1] = w;
}
void power(int F[2][2], int n) {
	if (n == 0 || n == 1)
		return;

	int M[2][2] = {{1,1}, {1,0}};

	power(F, n/2);
	multiply(F,F);

	if (n%2 != 0)
		multiply(F, M);
}
int fib(int n) {
	if (n < 0)
		throw invalid_argument("n must be >= 0");

	int F[2][2] = {{1,1}, {1,0}};
	if (n == 0)
		return 0;
	power(F, n-1);
	return F[0][0];
}

















// tests

const lest::test tests[] = {
    CASE("huge Fibonacci") {
        const int actual = fib(100000000000);
        const int expected = 0;
        EXPECT(actual == expected);
    },
    CASE("zeroth Fibonacci") {
        const int actual = fib(0);
        const int expected = 0;
        EXPECT(actual == expected);
    },
    CASE("first Fibonacci") {
        const int actual = fib(1);
        const int expected = 1;
        EXPECT(actual == expected);
    },
    CASE("second Fibonacci") {
        const int actual = fib(2);
        const int expected = 1;
        EXPECT(actual == expected);
    },
    CASE("third Fibonacci") {
        const int actual = fib(3);
        const int expected = 2;
        EXPECT(actual == expected);
    },
    CASE("fifth Fibonacci") {
        const int actual = fib(5);
        const int expected = 5;
        EXPECT(actual == expected);
    },
    CASE("tenth Fibonacci") {
        const int actual = fib(10);
        const int expected = 55;
        EXPECT(actual == expected);
    },
    CASE("negative fibonacci") {
        EXPECT_THROWS(fib(-1));
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
