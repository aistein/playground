// you can use includes, for example:
// #include <algorithm>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

using namespace std;

string solution(string &S, int K) {
    // write your code in C++14 (g++ 6.2.0)

    // Note: we cannot use the string.delete() function because it is O(n), which could
    // bring us to O(n^2) worst-case time complexity.

	// get the number of non-hyphen characters
	int cnt = 0;
	for (int i = 0; i < S.length(); i++)
		if (S[i] != '-') cnt++;

	// number of items in first group
	int fst = cnt % K;
	int fst_cntr = fst - 1;

	// counter to help place hyphens
	int k_cntr = K;

	// index for new string, and the new empty string
	int grps = cnt / K + (fst > 0); // accounts for "odd" case
	int hyph = grps - 1;
	string Q = string(cnt + hyph, ' ');
	int q_idx = 0;

	// fill the new string, correcting as we go
	for (int i = 0; i < S.length(); i++) {
		if (S[i] != '-') {
			if ( fst && fst_cntr > 0 ) {
				Q[q_idx++] = toupper(S[i]);
				fst_cntr--;
			} else if ( fst && fst_cntr == 0 ) {
				Q[q_idx++] = toupper(S[i]);
				Q[q_idx++] = '-';
				fst_cntr--;
			} else if ( k_cntr-- > 0 ) {
				Q[q_idx++] = toupper(S[i]);
			} else {
				Q[q_idx++] = '-';
				Q[q_idx++] = toupper(S[i]);
				k_cntr = K;
			}
		}
	}

	return Q;
}

int main(int argc, char** argv){

	string s = "2j4-k2-dwA";
	cout << solution(s, 4) << endl;

	s = "ac4d-b-5-3-2a";
	cout << solution(s, 4) << endl;

	s = "2-4A0r7-4k";
	cout << solution(s, 3) << endl;

	return 0;
}
