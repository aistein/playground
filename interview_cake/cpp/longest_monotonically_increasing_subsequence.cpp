#include <iostream>
#include <vector>
#include <stack>

// C++11 Lest unit testing framework
#include "lest.hpp"

using namespace std;

void printSequence( vector<int> theVector, vector<int> indexOfPrevInSequence, int finalIndex) {
	int currIndex = finalIndex;
	stack<int> theStack;

	// build up the longest sequence backwards into a stack
	while( currIndex >= 0 ) {
		theStack.push( theVector[currIndex] );
		currIndex = indexOfPrevInSequence[currIndex];
	}

	// print front to back by popping off the stack
	while ( !theStack.empty() ) {
		cout << theStack.top() << " ";
		theStack.pop();
	}
	cout << endl;
}


int longestIncreasingSequence( vector<int> theVector ) {
	vector<int> maxLengthEndingAt ( theVector.size(), 1 );
	vector<int> indexOfPrevInSequence ( theVector.size(), -1 );
	int finalIndex = -1;
	int finalMax = 1;
	for ( int i = 1; i < theVector.size(); i++ ) {
		int max = 0;
		int argmax = -1;
		int iValue = theVector[i];
		for ( int j = 0; j < i; j++ ) {
			if ( iValue > theVector[j] && maxLengthEndingAt[j] >= max ) {
				max = maxLengthEndingAt[j];
				argmax = j;
			}
		}
		if ( 1 + max >= finalMax ) {
			finalMax = 1 + max;
			finalIndex = i;
		}
		maxLengthEndingAt[i] = 1 + max;
		indexOfPrevInSequence[i] = argmax;
	}
	printSequence( theVector, indexOfPrevInSequence, finalIndex );
	return finalMax;
}

const lest::test tests[] = {
	CASE("shorter then longer") {
        auto theVector = {1, 2, 5, 8, 3, 6, 7};
        EXPECT(longestIncreasingSequence(theVector) == 5);
    },
	CASE("longer then shorter") {
		auto theVector = {1, 2, 3, 4, 5, 0, 1, 2, 3};
        EXPECT(longestIncreasingSequence(theVector) == 5);
	},
	CASE("very long vector") {
		auto theVector = {1, 8, 12, 3, 5, 2, 6, 20, 11, 3, 3, 3, 2, 10, 17, 18};
        EXPECT(longestIncreasingSequence(theVector) == 7);
	},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
