#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    bool isWord;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        isWord = false;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isWord = true;
    }

    bool search(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isWord;
    }

    void autoComplete(string prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                cout << "Нет вариантов";
                return;
            }
            current = current->children[c];
        }
        vector<string> suggestions;
        autoCompleteHelper(current, prefix, suggestions);
        if (suggestions.empty()) {
            cout << "Нет вариантов";
        }
        else {
            cout << "Предложения :" << endl;
            for (string word : suggestions) {
                cout << word << endl;
            }
        }
    }

private:
    void autoCompleteHelper(TrieNode* node, string word, vector<string>& suggestions) {
        if (node->isWord) {
            suggestions.push_back(word);
        }
        for (auto it : node->children) {
            char c = it.first;
            autoCompleteHelper(it.second, word + c, suggestions);
        }
    }
};

int main() {

    setlocale(LC_ALL, "Russian");

    Trie trie;
    trie.insert("apple");
    trie.insert("application");
    trie.insert("banana");
    trie.insert("doll");
    trie.insert("cat");
    trie.insert("carrot");

    while (true) {
        string input;
        cout << "Введите слово: ";
        cin >> input;
        trie.autoComplete(input);
        cout << endl;
    }

    return 0;
}