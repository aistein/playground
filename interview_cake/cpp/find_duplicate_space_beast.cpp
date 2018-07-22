#include <iostream>
#include <vector>
#include <limits>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

unsigned int findDuplicate(const vector<unsigned int>& theVector)
{
    // find a number that appears more than once ... in O(n) time

	// error case: < two numbers
	if (theVector.size() < 2) {
		throw invalid_argument("vector must be at least size 2.");
	}

	// corner case: two numbers
	if (theVector.size() == 2) {
		return (theVector[0] == theVector[1]) ? theVector[0] : std::numeric_limits<double>::quiet_NaN();
	}

	// normal case: N + 1 numbers in the range 1...N
	int N = theVector.size() - 1;
	int position = N + 1;

	// 1. To get inside of a loop, walk forward N steps. Optimization: check for self loops
	for (auto k = 0 ; k < N ; k++) {
		// if we are at a self-loop, then the current position is the repeated number
		if (theVector[position - 1] == position) {
			return position;
		}
		// otherwise update the position
		position = theVector[position - 1];
	}


	// 2. To find the length of the cycle, step forward from current position until loop-back
	int tail = theVector[position - 1];
	int cycleLength = 1;
	while (tail != position) {
		tail = theVector[tail - 1];
		++cycleLength;
	}


	// 3a. sub-step: need to walk cycleLength steps to intialize the tail
	position = tail = N + 1;
	for (auto k = 0 ; k < cycleLength ; k++) {
		tail = theVector[tail - 1];
	}
	// 3b. To find 1st node in cycle, "walk the stick" of length cycleLength
	//     incrementally down the list until front == back
	while (tail != position) {
		position = theVector[position - 1];
		tail = theVector[tail - 1];
	}

	// The position we're left at is the first node in the cycle, thus also the duplicate number
	return position;
}


















// tests

const lest::test tests[] = {
    CASE("just the repeated number") {
        const vector<unsigned int> numbers {1, 1};
        const auto expected = 1;
        const auto actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    },
    CASE("short vector") {
        const vector<unsigned int> numbers {1, 2, 3, 2};
        const auto expected = 2;
        const auto actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    },
    CASE("medium vector") {
        const vector<unsigned int> numbers {1, 2, 5, 5, 5, 5};
        const auto expected = 5;
        const auto actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    },
    CASE("long vector") {
        const vector<unsigned int> numbers {4, 1, 4, 8, 3, 2, 7, 6, 5};
        const auto expected = 4;
        const auto actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    },
    CASE("another long vector") {
        const vector<unsigned int> numbers {4, 1, 4, 2, 3, 2, 7, 6, 5};
        const auto expected = 4;
        const auto actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
