// tree.h
#ifndef TREE_H
#define TREE_H
#include <fstream>
#include "contactNode.h"

using namespace std;

class tree {
// private:
public:
    contactNode* root;
    ofstream outf;
    ifstream myFileStream;

    int numchck(long long int d);
    int mailchck(char a[]);
    void inordertrav(contactNode* t);

// public:
    tree();
    ~tree();

    void create();
    void create2(contactNode* p);
    void inorder();
    void writeExisting();
    void filee(contactNode* t);
    contactNode* minValueNode(contactNode* l);
    contactNode* deleteNode(contactNode* root, char a[20]);
    contactNode* edit(contactNode* root, char a[]);
    void searc(contactNode* root, char a[]);
    
};

#endif // TREE_H
