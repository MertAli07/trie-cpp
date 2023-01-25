#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include "Node.h"
#include "Trie.h"

using namespace std;

int main(int argc, char** argv) {
    //Getting the input from .txt file
    vector<string> data;
    fstream new_file;
    new_file.open(argv[1], ios::in);
    string line;
    while (getline (new_file, line))
    {
        data.push_back(line);
    }
    new_file.close();

    //Initializing the trie
    Node* root = new Node();
    Trie* dothraki = new Trie(root);

    //Processing the input file
    for(string s: data)
    {
        if(s[0] == 'i')
        {
            string inp = s.substr(7, s.length());
            inp.pop_back();
            vector<string> temp;
            stringstream test(inp);
            string segment;
            while(getline(test, segment, ','))
            {
                temp.push_back(segment);
            }
            dothraki->insert(root, temp[0], temp[1], 0, argv[2]);
        }
        else if(s[0] == 's')
        {
            string inp = s.substr(7, s.length());
            inp.pop_back();
            dothraki->search(root, inp, 0, argv[2]);

        }
        else if(s[0] == 'l')
        {
            char str[30];
            dothraki->list(root, str, 0, 0, argv[2]);
        }
        else if(s[0] == 'd')
        {
            string inp = s.substr(7, s.length());
            inp.pop_back();
            dothraki->deleteKey(root, inp, 0, argv[2]);
        }
        else
        {
            cout << "Invalid operation in input file!" << endl;
        }
    }
    return 0;
}
