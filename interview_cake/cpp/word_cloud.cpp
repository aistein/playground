#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

class WordCloudData
{
private:
    unordered_map<string, size_t> wordsToCounts_;

    // if a character is special, it's part of the word!
    bool isspecial(const char &prev, const char &curr)
    {
        if (prev != '\0' && isalpha(prev) && curr == '-') return true;
        if (prev != '\0' && isalpha(prev) && curr == '\'') return true;
        return false;
    }

    vector<string> splitWords(const string& inputString)
    {
        vector<string> words;

        size_t currentWordStartIndex = 0;
        size_t currentWordLength = 0;
        char prev = '\0';

        for (size_t i = 0; i < inputString.length(); ++i) {
            char character = inputString[i];

            // if this is part of a word, "record" it by keeping the index
            if (isalpha(character) || isspecial(prev, character)) {
                if (currentWordLength == 0) {
                    currentWordStartIndex = i;
                }
                ++currentWordLength;
            }
            else {
                if ( currentWordStartIndex != (currentWordStartIndex + currentWordLength) ) {
                    // don't want to push empty words into the vector
                    string currentWord = inputString.substr(currentWordStartIndex, currentWordLength);
                    words.push_back(move(currentWord));
                }
                currentWordLength = 0;
            }

            prev = character;
        }

        // push the last word
        if ( currentWordStartIndex != (currentWordStartIndex + currentWordLength) ) {
            // don't want to push empty words into the vector
            string currentWord = inputString.substr(currentWordStartIndex, currentWordLength);
            words.push_back(move(currentWord));
        }

        return words;
    }

    void populateWordsToCounts(const string& inputString)
    {
        // count the frequency of each word

        // put the words into an unordered map, histogram style
        // - if it was the first word in the sentence, treat it as lowercase
        vector<string> words = splitWords(inputString);
        for (string word : words) {
            string lowerCaseWord = word;
            string upperCaseWord = word;
            lowerCaseWord[0] = tolower(lowerCaseWord[0]);
            upperCaseWord[0] = toupper(upperCaseWord[0]);

            // if we find the word in its current case, increment it
            if (wordsToCounts_.find(word) != wordsToCounts_.end()) {
                wordsToCounts_[word]++;
            // if we find the word in lower case, increment that
            } else if (wordsToCounts_.find(lowerCaseWord) != wordsToCounts_.end() ) {
                wordsToCounts_[lowerCaseWord]++;
            // if we find the word in upper case, remove it, and replace with lower case
            } else if (wordsToCounts_.find(upperCaseWord) != wordsToCounts_.end() ) {
                size_t tmp = wordsToCounts_[upperCaseWord];
                wordsToCounts_.erase(upperCaseWord);
                wordsToCounts_[lowerCaseWord] = tmp + 1;
            // if the word is not in the map yet, add it!
            } else {
                wordsToCounts_[word] = 1;
            }
        }
    }

public:
    WordCloudData (const string& inputString)
    {
        populateWordsToCounts(inputString);
    }

    const unordered_map<string, size_t> getWordsToCounts() const
    {
        return wordsToCounts_;
    }
};


















// tests

// There are lots of valid solutions for this one. You
// might have to edit some of these tests if you made
// different design decisions in your solution.

const lest::test tests[] = {
    CASE("simple sentence") {
        const string text = "I like cake";
        const unordered_map<string, size_t> expected { {"I", 1}, {"like", 1}, {"cake", 1} };
        const WordCloudData actual(text);
        EXPECT(actual.getWordsToCounts() == expected);
    },
    CASE("longer sentence") {
        const string text = "Chocolate cake for dinner and pound cake for dessert";
        const unordered_map<string, size_t> expected {
            {"and", 1},  {"pound", 1}, {"for", 2},
            {"dessert", 1}, {"Chocolate", 1}, {"dinner", 1}, {"cake", 2}
        };
        const WordCloudData actual(text);
        EXPECT(actual.getWordsToCounts() == expected);
    },
    CASE("punctuation") {
        const string text = "Strawberry short cake? Yum!";
        const unordered_map<string, size_t> expected {
            {"cake", 1}, {"Strawberry", 1}, {"short", 1}, {"Yum", 1}
        };
        const WordCloudData actual(text);
        EXPECT(actual.getWordsToCounts() == expected);
    },
    CASE("hyphenated words") {
        const string text = "Dessert - mille-feuille cake";
        const unordered_map<string, size_t> expected {
            {"cake", 1}, {"Dessert", 1}, {"mille-feuille", 1}
        };
        const WordCloudData actual(text);
        EXPECT(actual.getWordsToCounts() == expected);
    },
    CASE("ellipses between words") {
        const string text = "Mmm...mmm...decisions...decisions";
        const unordered_map<string, size_t> expected { {"mmm", 2}, {"decisions", 2} };
        const WordCloudData actual(text);
        EXPECT(actual.getWordsToCounts() == expected);
    },
    CASE("apostrophes") {
        const string text = "Allie's Bakery: Sasha's Cakes";
        const unordered_map<string, size_t> expected {
            {"Bakery", 1}, {"Cakes", 1}, {"Allie's", 1}, {"Sasha's", 1}
        };
        const WordCloudData actual(text);
        EXPECT(actual.getWordsToCounts() == expected);
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
