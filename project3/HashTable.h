#include <vector>
#include <list>
#include <WordEntry.h>

class HashTable {
private:
    int tableSize;
    std::vector<std::list<WordEntry>> table;

public:
    HashTable(int size) : tableSize(size), table(size) {}

    // Hash function
    int hash(const std::string& word) {
        int hashCode = 0;
        for (size_t i = 0; i < word.size(); ++i)
            hashCode = hashCode * 31 + static_cast<int>(word[i]);
        return std::abs(hashCode) % tableSize;
    }

    // Method to insert or search for a word in the hash table
    WordEntry& insertOrSearch(const std::string& word) {
        int index = hash(word);
        for (auto& entry : table[index]) {
            if (entry.word == word) {
                entry.occurrences++;
                entry.totalSteps++; // Word found, increment step count
                return entry;
            }
        }
        // Word not found, add it to the end of the list
        WordEntry newEntry(word);
        newEntry.occurrences = 1;
        table[index].push_back(newEntry);
        return table[index].back();
    }

     const std::vector<std::list<WordEntry>>& getTable() const {
        return table;
    }
};
