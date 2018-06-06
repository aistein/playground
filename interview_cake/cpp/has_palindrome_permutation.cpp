#include <iostream>
#include <string>
#include <unordered_set>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

bool hasPalindromePermutation(const string& str)
{
    // keep a list of characters which are not "paired"
    // this effectively leaves us with a set of characters for which there were
    // an odd number of replicas in the original string
    unordered_set<char> unpairedCharacters;
    for (int i = 0; i < str.length(); i++) {
        if ( unpairedCharacters.find(str[i]) == unpairedCharacters.end() ) {
            unpairedCharacters.insert(str[i]);
        } else {
            unpairedCharacters.erase(str[i]);
        }
    }

    // if there are more than one character groupings of odd length,
    // then there is no possible permutation of str that could be a palindrome
    if (unpairedCharacters.size() > 1)
        return false;
    return true;
}

// tests

const lest::test tests[] = {
    CASE("permutation with odd number of chars") {
        const auto result = hasPalindromePermutation("aabcbcd");
        EXPECT(result == true);
    },
    CASE("permutation with even number of chars") {
        const auto result = hasPalindromePermutation("aabccbdd");
        EXPECT(result == true);
    },
    CASE("no permutation with odd number of chars") {
        const auto result = hasPalindromePermutation("aabcd");
        EXPECT(result == false);
    },
    CASE("no permutation with even number of chars") {
        const auto result = hasPalindromePermutation("aabbcd");
        EXPECT(result == false);
    },
    CASE("empty string") {
        const auto result = hasPalindromePermutation("");
        EXPECT(result == true);
    },
    CASE("one character string") {
        const auto result = hasPalindromePermutation("a");
        EXPECT(result == true);
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
