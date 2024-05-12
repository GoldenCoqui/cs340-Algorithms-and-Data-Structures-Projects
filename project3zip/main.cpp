#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct WordEntry {
    string word;
    int occurrences;
    int totalSteps;

    WordEntry(const std::string& w) : word(w), occurrences(0), totalSteps(0) {}
};

class HashTable {
private:
    int tableSize;
    std::vector<std::list<WordEntry>> table;

public:
    HashTable(int size) : tableSize(size), table(size) {}

    int hash(const std::string& word) {
        int hashCode = 0;
        for (size_t i = 0; i < word.size(); ++i)
            hashCode = hashCode * 31 + static_cast<int>(word[i]);
        return std::abs(hashCode) % tableSize;
    }

    WordEntry& insertOrSearch(const std::string& word) {
        int index = hash(word);
        for (auto& entry : table[index]) {
            if (entry.word == word) {
                entry.occurrences++;
                entry.totalSteps++; 
                return entry;
            }
        }
        WordEntry newEntry(word);
        newEntry.occurrences = 1;
        table[index].push_back(newEntry);
        return table[index].back();
    }

     const std::vector<std::list<WordEntry>>& getTable() const {
        return table;
    }
};

int main() {
    HashTable hashTable(500);

    std::ifstream inputFile("LittleWomen.txt");

    std::string word;
    while (inputFile >> word) {
        WordEntry& entry = hashTable.insertOrSearch(word);
        entry.totalSteps++; 
    }

    inputFile.close();

    std::ofstream outputFile("output.csv");

    outputFile << "Word,Occurrences,Steps" << std::endl;

    for (const auto& entries : hashTable.getTable()) {
        for (const WordEntry& entry : entries) {
            outputFile << entry.word << "," << entry.occurrences << "," << entry.totalSteps << std::endl;
        }
    }

    outputFile.close();

    return 0;
}
