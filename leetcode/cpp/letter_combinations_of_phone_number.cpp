#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef unordered_set<string> stringset;
typedef unordered_map<char,stringset> hashtable;

hashtable LETTERS_BY_DIGIT({
    {'0', stringset()},
    {'1', stringset()},
    {'2', stringset( {"a","b","c"} )},
    {'3', stringset( {"d","e","f"} )},
    {'4', stringset( {"g","h","i"} )},
    {'5', stringset( {"j","k","l"} )},
    {'6', stringset( {"m","n","o"} )},
    {'7', stringset( {"p","q","r","s"} )},
    {'8', stringset( {"t","u","v"} )},
    {'9', stringset( {"w","x","y","z"} )}
});

stringset _buildPrefixesIterative ( stringset partial_solution, string digits ) {
    for (auto& digit : digits) {
        stringset tmp = partial_solution;
        for (auto &prefix : tmp ) {
            for (auto& letter : LETTERS_BY_DIGIT[ digit ] ) {
                partial_solution.insert( prefix + letter );
                partial_solution.erase( prefix );
            }
        }
    }
    
    return partial_solution;
}

vector<string> letterCombinations(string digits) {
    
    // corner case
    if (digits.length() == 0)
        return vector<string> ();
    
    stringset solution = _buildPrefixesIterative( LETTERS_BY_DIGIT[ digits[0] ],
                                            digits.substr(1) );
    
    return vector<string>(solution.begin(), solution.end());
}

int main(int argc, char** argv) {

    if (argc < 2) {
        cout << "usage: ./letter_combinations_of_phone_number \"<phone-number>\"\n";
        exit(-1);
    }
    string phone_number = argv[1];
    cout << phone_number << endl;

    string output = "";
    for (auto &combo : letterCombinations( phone_number )) {
        output += " " + combo;
    }
    cout << output << endl;

    return 0;
}