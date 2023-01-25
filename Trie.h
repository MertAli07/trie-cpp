
#ifndef ASSIGNMENT4_TRIE_H
#define ASSIGNMENT4_TRIE_H
#include "Node.h"

class Trie {
public:
    Node* pNode;
    Trie();
    Trie(Node* root);
    ~Trie();

    void writeOutput(string outputFile, string text);
    void insert(Node* &root , string key, string value, int d, string outFile);
    void search(Node* &root, string key, int d, string outFile);
    void list(Node* &root, char str[], int d, int bl, string outFile);
    void deleteKey(Node* &root, string key, int d, string outFile);

};


#endif //ASSIGNMENT4_TRIE_H
