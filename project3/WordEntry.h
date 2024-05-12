#include <string>
using namespace std;
struct WordEntry {
    string word;
    int occurrences;
    int totalSteps;

    WordEntry(const std::string& w) : word(w), occurrences(0), totalSteps(0) {}
};
