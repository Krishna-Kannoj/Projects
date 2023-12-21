// contactNode.cpp
#include "contactNode.h"
#include <cstring>

contactNode::contactNode() : number(0), left(nullptr), right(nullptr) {
    memset(fname, 0, sizeof(fname));
    memset(lname, 0, sizeof(lname));
    memset(email, 0, sizeof(email));
}

contactNode::~contactNode() {
    // Add any necessary cleanup code here
}
