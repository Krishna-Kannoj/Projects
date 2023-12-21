// contactNode.h
#ifndef CONTACT_NODE_H
#define CONTACT_NODE_H

class contactNode {
// private:
public:
    long long int number;
    char fname[20], lname[20], email[40];
    contactNode* left, *right;

    friend class tree;

// public:
    contactNode();
    ~contactNode();
};

#endif // CONTACT_NODE_H
