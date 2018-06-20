#include <iostream>
#include <sstream>
#include <vector>
#include <experimental/filesystem>

// FIXME: MacOSX doesn't support c++17 filesystem library, and so I'm going to solve this problem in another language

using namespace std;

#define DATA "/Users/alexstein/Code/Repositories/playground/interview_cake/data"

class FilePaths
{
public:
    string duplicatePath_;
    string originalPath_;

    FilePaths(const string& duplicatePath, const string& originalPath) :
        duplicatePath_(duplicatePath),
        originalPath_(originalPath)
    {
    }

    string toString() const
    {
        ostringstream str;
        str << "(original: " << originalPath_
            << ", duplicate: " << duplicatePath_ << ')';
        return str.str();
    }
};

vector<FilePaths> findDuplicateFiles(const string& startingDirectory)
{
    // find the duplicate files, so we can clean them up
    filesystem::path p(startingDirectory);

    // error checking
    if (!exists(p) || !is_directory(p)) {
        cout << p << "is not a path\n";
        throw std::invalid_argument;
    }

    recursive_directory_iterator begin(p);

    for (auto& f : begin) {
        cout << f << 'n';
    }

    return vector<FilePaths>();
}

int main(int argc, char** argv)
{
    const auto duplicates = findDuplicateFiles($DATA);
    if (duplicates.empty()) {
        cout << "There are no duplicate files." << endl;
    } else {
        for (const auto duplicate: duplicates) {
            cout << duplicate.toString() << endl;
        }
        cout << "Total: " << duplicates.size() << " duplicate file(s)." << endl;
    }
    return 0;
}
