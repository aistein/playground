#include <iostream>
#include <vector>
#include <unordered_set>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

bool canTwoMoviesFillFlight(const vector<int>& movieLengths, int flightLength)
{
    // error checking
    if (movieLengths.size() <= 1)
        throw std::length_error("must have at least two movies.");

    unordered_set<int> H;
    for (int i = 0; i < movieLengths.size(); i++) {
        int timeRemaining = flightLength - movieLengths[i];

        // Check if there is a satisfactory second movie
        // before inserting the current movie into the hash table.
        // This insures we don't accidentally take the same movie twice.
        auto secondMovie = H.find(timeRemaining);
        if ( secondMovie != H.end() ) {
            return true;
        }

        // If no such movie existed, push the current one into the hash table
        // and move on
        H.insert(movieLengths[i]);
    }

    // if we've reached the end, then there is no satisfactory movie combo
    return false;
}

// tests

const lest::test tests[] = {
    CASE("small selection true") {
        const auto movieLengths = vector<int> {1, 2, 3};
        const auto flightLength = 5;
        const auto actual = canTwoMoviesFillFlight(movieLengths, flightLength);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("small selection false") {
        const auto movieLengths = vector<int> {1, 2, 3};
        const auto flightLength = 6;
        const auto actual = canTwoMoviesFillFlight(movieLengths, flightLength);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("larger selection true") {
        const auto movieLengths = vector<int> {1, 4, 3, 1, 2, 2, 3};
        const auto flightLength = 6;
        const auto actual = canTwoMoviesFillFlight(movieLengths, flightLength);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("larger selection false") {
        const auto movieLengths = vector<int> {1, 3, 5, 2, 1, 3};
        const auto flightLength = 9;
        const auto actual = canTwoMoviesFillFlight(movieLengths, flightLength);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("short flight") {
        const auto movieLengths = vector<int> {1, 4, 5, 3};
        const auto flightLength = 1;
        const auto actual = canTwoMoviesFillFlight(movieLengths, flightLength);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("zero movies") {
        EXPECT_THROWS(canTwoMoviesFillFlight({}, 3));
    },
    CASE("one movie") {
        EXPECT_THROWS(canTwoMoviesFillFlight({1}, 3));
    },
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
