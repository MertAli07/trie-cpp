
#include "Trie.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

Trie::Trie() {}
Trie::Trie(Node* root)
{
    this->pNode = root;
}
Trie::~Trie() {}

Node* getnode()
{
    Node* pNode = new Node();
    return pNode;
}

void Trie::writeOutput(string outputFile, string text)
{
    ofstream outputFile2;
    outputFile2.open(outputFile, ios_base::app);
    outputFile2 << text << endl;
    outputFile2.close();
}

void Trie::insert(Node* &root , string key, string val, int d, string outFile)
{
    if (d == key.length())
    {
        if(root->value == val)
        {
            writeOutput(outFile, "\""+key+"\""+" already exist");
            return;
        }
        else if(!(root->value.empty()))
        {
            writeOutput(outFile, "\""+key+"\""+" was updated");
            root->value = val;
            return;
        }
        else if(root->value.empty())
        {
            root->value = val;
            writeOutput(outFile, "\""+key+"\""+" was added");
            return;
        }
    }
    char c = key[d];
    if(root->next.empty())
    {
        Node* x = getnode();
        x->key = c;
        root->next.push_back(x);
        insert(root->next.back(), key, val, d+1, outFile);
    }
    else if(!(root->next.empty())) //Branching
    {
        for(int i = 0; i<root->next.size(); i++)
        {
            if(root->next[i]->key == c)
            {
                insert(root->next[i], key, val, d+1, outFile);
                return;
            }
        }
        Node* x = getnode();
        x->key = c;
        root->next.push_back(x);
        insert(root->next.back(), key, val, d+1, outFile);
    }
}

void Trie::search(Node *&root, string key, int d, string outFile)
{
    if(d == key.length())
    {
        if(root->value.empty())
        {
            writeOutput(outFile, "\"not enough Dothraki word\"");
            return;
        }
        else
        {
            writeOutput(outFile, "\"The English equivalent is "+root->value+"\"");
            return;
        }
    }
    char c = key[d];
    vector<char> tmp;
    for(Node* p: root->next)
    {
        tmp.push_back(p->key);
    }
    if(count(tmp.begin(), tmp.end(), c) == 0)
    {
        if(d == 0)
        {
            writeOutput(outFile, "\"no record\"");
            return;
        }
        else
        {
            writeOutput(outFile, "\"incorrect Dothraki word\"");
            return;
        }
    }
    for(int i = 0; i<root->next.size(); i++)
    {
        if(root->next[i]->key == c)
        {
            search(root->next[i], key, d+1, outFile);
            break;
        }
    }
}

void Trie::list(Node *&root, char str[], int d, int bl, string outFile)
{
    if(root->next.empty())
    {
        str[d] = '\0';
        ofstream outputFile2;
        outputFile2.open(outFile, ios_base::app);
        for(int i = 0; i<bl; i++) {outputFile2 << "\t";}
        outputFile2 << "-" << str << "("+root->value+")" << endl;
        outputFile2.close();
        return;
    }
    if(root->next.size() == 1) //No branching
    {
        if(!(root->value.empty()))
        {
            str[d] = '\0';
            ofstream outputFile2;
            outputFile2.open(outFile, ios_base::app);
            for(int i = 0; i<bl; i++) {outputFile2 << "\t";}
            outputFile2 << "-" << str << "("+root->value+")" << endl;
            outputFile2.close();
        }
    }
    if(root->next.size() > 1) //Branching
    {
        str[d] = '\0';
        ofstream outputFile2;
        outputFile2.open(outFile, ios_base::app);
        for(int i = 0; i<bl; i++) {outputFile2 << "\t";}
        if(root->value.empty() && d != 0)
        {
            outputFile2 << "-" << str << endl;
        }
        else if(!(root->value.empty()) && d != 0)
        {
            outputFile2 << "-" << str << "("+root->value+")" << endl;
        }
        outputFile2.close();
    }
    //sorting
    vector<char> temp;
    for(Node* p: root->next)
    {
        temp.push_back(p->key);
    }
    sort(temp.begin(), temp.end());
    vector<Node*> pointers;
    for(char c: temp)
    {
        for(Node* p: root->next)
        {
            if(p->key == c)
            {
                pointers.push_back(p);
            }
        }
    }
    if(pointers.size() > 1 && d != 0) {bl++;}
    //next step
    for(Node* p: pointers)
    {
        str[d] = p->key;
        list(p, str, d+1, bl, outFile);
    }
}

void Trie::deleteKey(Node *&root, string key, int d, string outFile)
{
    if(d == key.length())
    {
        if(root->value.empty())
        {
            writeOutput(outFile, "\"not enough Dothraki word\"");
            return;
        }
        else if(root->next.empty())
        {
            writeOutput(outFile, "\""+key+"\""+" deletion is successful");
            delete root;
            root = NULL;
            return;
        }
        else
        {
            writeOutput(outFile, "\""+key+"\""+" deletion is successful");
            root->value.erase();
            return;
        }
    }
    char c = key[d];
    vector<char> tmp;
    for(Node* p: root->next)
    {
        tmp.push_back(p->key);
    }
    if(count(tmp.begin(), tmp.end(), c) == 0)
    {
        if(d == 0)
        {
            writeOutput(outFile, "\"no record\"");
            return;
        }
        else
        {
            writeOutput(outFile, "\"incorrect Dothraki word\"");
            return;
        }
    }
    for(int i = 0; i<root->next.size(); i++)
    {
        if(root->next[i]->key == c)
        {
            deleteKey(root->next[i], key, d+1, outFile);
            if(root->next[i] == NULL)
            {
                root->next.erase(root->next.begin()+i);
            }
        }
    }

    if(root->next.empty() && root->value.empty())
    {
        delete root;
        root = NULL;
        return;
    }
}