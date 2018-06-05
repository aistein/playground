#include <iostream>
#include <vector>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

bool isSingleRiffle(
    const vector<int>& half1,
    const vector<int>& half2,
    const vector<int>& shuffledDeck
)
{
    size_t half1Index = 0;
    size_t half2Index = 0;

    for (int card : shuffledDeck) {
        // if there are cards in half1
        // and the card in half1 is the same as the top
        // then we could still have a single riffle
        if (half1Index < half1.size() && card == half1[half1Index]) {
            ++half1Index;
        }


        // if there are cards in half2
        // and the card in half2 is the same as top
        // then we could still ahve a single riffle
        else if (half2Index < half2.size() && card == half2[half2Index]) {
            ++half2Index;
        }

        // if the top card of shuffledDeck doesn't match either half's top
        // then this could not have come from a single riffle
        else {
            return false;
        }
    }

    // we've made it through the entire shuffledDeck, so it must have come
    // from a single riffle.
    return true;
}
// tests

const lest::test tests[] = {
    CASE("small deck single riffle") {
        const auto half1 = vector<int> {8, 5};
        const auto half2 = vector<int> {7, 10};
        const auto shuffledDeck = vector<int> {7, 8, 10, 5};
        const auto actual = isSingleRiffle(half1, half2, shuffledDeck);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("small deck not single riffle") {
        const auto half1 = vector<int> {8, 5};
        const auto half2 = vector<int> {7, 10};
        const auto shuffledDeck = vector<int> {5, 8, 10, 7};
        const auto actual = isSingleRiffle(half1, half2, shuffledDeck);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("larger deck single riffle") {
        const auto half1 = vector<int> {1, 23, 17, 43, 11};
        const auto half2 = vector<int> {25, 32, 6, 8};
        const auto shuffledDeck = vector<int> {1, 23, 17, 25, 43, 32, 6, 11, 8};
        const auto actual = isSingleRiffle(half1, half2, shuffledDeck);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("larger deck not single riffle") {
        const auto half1 = vector<int> {1, 23, 17, 43, 11};
        const auto half2 = vector<int> {25, 32, 6, 8};
        const auto shuffledDeck = vector<int> {1, 23, 17, 11, 43, 32, 6, 25, 8};
        const auto actual = isSingleRiffle(half1, half2, shuffledDeck);
        const auto expected = false;
        EXPECT(actual == expected);
    },
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
