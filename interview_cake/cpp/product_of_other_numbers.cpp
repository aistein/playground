#include <iostream>
#include <vector>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

vector<int> getProductsOfAllIntsExceptAtIndex(const vector<int>& intVector)
{
    vector<int> M(intVector);
    vector<int> O(intVector);
    int n = intVector.size();
    int pivot = 1;

    // corner cases
    if (n <= 1){
        throw std::length_error("input is too small.");
    }
    if (n == 2){
        O[0] = intVector[1];
        O[1] = intVector[0];
        return O;
    }
    if (n == 3){
        O[0] = intVector[1]*intVector[2];
        O[1] = intVector[0]*intVector[2];
        O[2] = intVector[0]*intVector[1];
        return O;
    }

    // first iteration fills M backwards
    for (int i = n - 2; i >= pivot; i--){
        M[i] = intVector[i] * M[i+1];
    }
    O[0] = M[pivot];

    // now dynamically fill the output and update M
    // left of pivot - product from A[0] upto A[pivot-1]
    // right of pivot - product from A[n-1] downto A[pivot+1]
    for (int i = pivot; i < n-1; i++){
        M[pivot] = M[pivot-1] * intVector[i];
        O[i] = M[pivot-1] * M[pivot+1];
        pivot++;
    }
    O[n-1] = M[pivot-1];

    return O;
}

// tests

const lest::test tests[] = {
    CASE("small vector") {
        const auto actual = getProductsOfAllIntsExceptAtIndex({1, 2, 3});
        const auto expected = vector<int> {6, 3, 2};
        EXPECT(actual == expected);
    },

    CASE("longer vector") {
        const auto actual = getProductsOfAllIntsExceptAtIndex({8, 2, 4, 3, 1, 5});
        const auto expected = vector<int> {120, 480, 240, 320, 960, 192};
        EXPECT(actual == expected);
    },

    CASE("vector has one zero") {
        const auto actual = getProductsOfAllIntsExceptAtIndex({6, 2, 0, 3});
        const auto expected = vector<int> {0, 0, 36, 0};
        EXPECT(actual == expected);
    },

    CASE("vector has two zeros") {
        const auto actual = getProductsOfAllIntsExceptAtIndex({4, 0, 9, 1, 0});
        const auto expected = vector<int> {0, 0, 0, 0, 0};
        EXPECT(actual == expected);
    },

    CASE("one negative number") {
        const auto actual = getProductsOfAllIntsExceptAtIndex({-3, 8, 4});
        const auto expected = vector<int> {32, -12, -24};
        EXPECT(actual == expected);
    },

    CASE("all negative numbers") {
        const auto actual = getProductsOfAllIntsExceptAtIndex({-7, -1, -4, -2});
        const auto expected = vector<int> {-8, -56, -14, -28};
        EXPECT(actual == expected);
    },

    CASE("error with empty vector") {
        EXPECT_THROWS(getProductsOfAllIntsExceptAtIndex({}));
    },

    CASE("error with one number") {
        EXPECT_THROWS(getProductsOfAllIntsExceptAtIndex({1}));
    },
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
