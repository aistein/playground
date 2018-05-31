#include <iostream>
#include <tuple>
#include <vector>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

tuple<int,char> minOwner(int a, int b)
{
    // TODO: error checking
    if (a <= b)
        return make_tuple(a, 'A');
    else
        return make_tuple(b, 'B');
}

vector<int> mergeSortedIntLists(const vector<int>& A, const vector<int>& B)
{
    int m = A.size();
    int n = B.size();

    // Corner Cases
    if (m == 0 || n == 0) {
        throw std::length_error("both lists must have at least one element.");
    }
    if (m == 1 && n == 1) {
        if (A[0] >= B[0])
            return vector<int> {B[0], A[0]};
        else
            return vector<int> {A[0], B[0]};
    }

    // General Case
    vector<int> O;
    int a_idx = 0;
    int b_idx = 0;
    int min;
    char owner;
    tie (min, owner) = minOwner(A[a_idx], B[b_idx]);
    for (int i = 0; i < m + n; i++) {
        O.push_back(min);
        if (owner == 'A') a_idx++;
        else b_idx++;
        // if we reach the end of one list, just continue with the other
        if (a_idx >= m) {
            min = B[b_idx];
            owner = 'B';
        } else if (b_idx >= n) {
            min = A[a_idx];
            owner = 'A';
        } else {
        // otherwise continue with minOwner paradigm
            tie (min, owner) = minOwner(A[a_idx], B[b_idx]);
        }
    }

    return O;
}

// tests

const lest::test tests[] = {
    CASE("small vectors") {
        const auto actual = mergeSortedIntLists({1}, {0});
        const auto expected = vector<int> {0, 1};
        EXPECT(actual == expected);
    },

    CASE("medium sized vectors") {
        const auto actual = mergeSortedIntLists({1, 2, 3}, {2, 3, 4});
        const auto expected = vector<int> {1, 2, 2, 3, 3, 4};
        EXPECT(actual == expected);
    },

    CASE("consecutively sorted") {
        const auto actual = mergeSortedIntLists({1,2,3,4}, {5,6,7,8});
        const auto expected = vector<int> {1,2,3,4,5,6,7,8};
        EXPECT(actual == expected);
    },

    CASE("reverse sorted") {
        const auto actual = mergeSortedIntLists({8,11,21,32}, {0,3,5,7});
        const auto expected = vector<int> {0,3,5,7,8,11,21,32};
        EXPECT(actual == expected);
    },

    CASE("different lengths") {
        const auto actual = mergeSortedIntLists({1,2,23}, {0,5,11,33,55});
        const auto expected = vector<int> {0,1,2,5,11,23,33,55};
        EXPECT(actual == expected);
    },

    CASE("error with one empty vector") {
        EXPECT_THROWS(mergeSortedIntLists({}, {1}));
    },

    CASE("error with two empty vectors") {
        EXPECT_THROWS(mergeSortedIntLists({}, {}));
    },
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
