
#ifndef ASSIGNMENT4_NODE_H
#define ASSIGNMENT4_NODE_H
#include <vector>
#include <string>
using namespace std;


class Node {
public:
    char key;
    string value;
    vector<Node*> next;

    Node();
    ~Node();

};


#endif //ASSIGNMENT4_NODE_H
