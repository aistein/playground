#include <iostream>
#include <vector>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

size_t changePossibilities(int amount, const vector<int>& denominations)
{
    // calculate the number of ways to make change

    //// corner cases
    // zero denominations
    if ( denominations.size() == 0) {
        return 0;
    }
    // one denomination
    if ( denominations.size() == 1) {
        return amount % denominations[0] > 0 ? 0 : 1;
    }

    // create and initialize vector counts
    // - waysOfDoingN[i] = # ways to make the value i
    // - this will only be true AFTER the termination of the algorithm!
    vector<int> waysOfDoingN (amount + 1, 0);
    waysOfDoingN[0] = 1;
    for (int j = 1; j <= amount; j++) {
        waysOfDoingN[j] = (j % denominations[0]) > 0 ? 0 : 1;
    }

    // build the answer bottom up:
    // - waysOfDoingN_1and2[n] = waysOfDoingN_1[n] + waysOfDoingN_1and2[n-2]
    // - the outside loop ranges over coin denominations
    // - the inside loop ranges over values from 1 to amount
    for (int i = 1; i < denominations.size(); i++) {
        int coinValue = denominations[i];
        for (int j = coinValue; j <= amount; j++) {
            if (j - coinValue < 0) break;
            waysOfDoingN[j] = waysOfDoingN[j] + waysOfDoingN[j-coinValue];
        }
    }



    return waysOfDoingN[amount];
}


















// tests

const lest::test tests[] = {
    CASE("sample input") {
        const size_t actual = changePossibilities(4, {1, 2, 3});
        const size_t expected = 4;
        EXPECT(actual == expected);
    },

    CASE("one way to make zero cents") {
        const size_t actual = changePossibilities(0, {1, 2});
        const size_t expected = 1;
        EXPECT(actual == expected);
    },

    CASE("no ways if no coins") {
        const size_t actual = changePossibilities(1, {});
        const size_t expected = 0;
        EXPECT(actual == expected);
    },

    CASE("big coin value") {
        const size_t actual = changePossibilities(5, {25, 50});
        const size_t expected = 0;
        EXPECT(actual == expected);
    },

    CASE("big target amount") {
        const size_t actual = changePossibilities(50, {5, 10});
        const size_t expected = 6;
        EXPECT(actual == expected);
    },

    CASE("change for one dollar") {
        const size_t actual = changePossibilities(100, {1, 5, 10, 25, 50});
        const size_t expected = 292;
        EXPECT(actual == expected);
    },
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
