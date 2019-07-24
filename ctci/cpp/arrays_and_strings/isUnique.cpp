#include <iostream>
#include <unordered_set>

using namespace std;

// hash-table version
bool isUnique(string S) {
	// base case
	if (S.length() <= 1) return true;

	// store found unique chars in an unordered_set
	unordered_set<char> unique_chars;
	for (char c : S) {
		if (unique_chars.find(c) != unique_chars.end()) return false;
		unique_chars.insert(c);
	}
	return true;
}

// mergesort function
void merge(string &A, int p, int q, int r) {
	int i, j, k;
	int n1 = q - p + 1;
	int n2 = r - q;
	string L, R;
	L = A.substr(p, n1);
	R = A.substr(q + 1, n2);
	i = j = 0;
	for (k = p; k <= r; k++) {
		if ( (j >= R.length() ) || (i < L.length() && L[i] <= R[j]) ) {
			A[k] = L[i++];
		}
		else {
			A[k] = R[j++];
		}
	}

}
void mergesort(string &S, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		mergesort(S, p, q);
		mergesort(S, q + 1, r);
		merge(S, p, q, r);
	}
}

// mergesort version
bool isUnique2(string S) {
	mergesort(S, 0, S.length() - 1);
	char prev = S.front();
	for (int i = 1; i < S.length(); i++) {
		if (prev == S[i]) return false;
		prev = S[i];
	}
	return true;
}

// bit-vector version
bool isUnique3(string S) {
	// assumes ASCII encoding

	// long long guarantees 64 bits, but we need 256 (4x64)
	long long checker0, checker1, checker2, checker3;
	checker0 = checker1 = checker2 = checker3 = 0;

	for (char c : S) {
		int val = c - '0';
		if (val >= 192) {
			if ((checker3 & (1 << (val - 192))) > 0) return false;
			checker3 |= (1 << (val - 192));
		} else if (val >= 128) {
			if ((checker2 & (1 << (val - 128))) > 0) return false;
			checker2 |= (1 << (val - 128));
		} else if (val >= 64) {
			if ((checker1 & (1 << (val - 64))) > 0) return false;
			checker1 |= (1 << (val - 64));
		} else {
			if ((checker0 & 1 << val) > 0) return false;
			checker0 |= (1 << val);
		}
	}
	return true;
}

int main(int argc, char** argv) {
	string s = "abcdgzqa";
	//printf("string s\"%s\" unique? %d\n", s.c_str(), isUnique(s));
	//printf("string s\"%s\" unique? %d\n", s.c_str(), isUnique2(s));
	printf("string s\"%s\" unique? %d\n", s.c_str(), isUnique3(s));

	s = "abcdgzq";
	//printf("string s\"%s\" unique? %d\n", s.c_str(), isUnique(s));
	//printf("string s\"%s\" unique? %d\n", s.c_str(), isUnique2(s));
	printf("string s\"%s\" unique? %d\n", s.c_str(), isUnique3(s));

	s = "AbCda";
	printf("string s\"%s\" unique? %d\n", s.c_str(), isUnique(s));
	return 0;
}
