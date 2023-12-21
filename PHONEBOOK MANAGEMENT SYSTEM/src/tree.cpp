// tree.cpp
#include "tree.h"
#include "contactNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>


using namespace std;

tree::tree() : root(nullptr) {}

tree::~tree() { }


int tree::numchck(long long int d) {
    int c = 0;
    while (d > 0) {
        c++;
        d /= 10;
    }
    if (c == 10) return 1;
    cout << "Number Invalid";
    return 0;
}

int tree::mailchck(char a[]) {
    int j = 0, i = 0;
    while (a[i] != '\0') {
        if (a[i] == '@') j++;
        i++;
    }
    if (j == 1) return 1;
    cout << "Email id Invalid";
    return 0;
}

void tree::inordertrav(contactNode* t) {
    if (t != nullptr) {
        inordertrav(t->left);
        cout << "\nContact Details:\n";
        cout << "First name: " << t->fname << "\tLast name: " << t->lname
             << "\nPhone Number: " << t->number << "\tEmail id: " << t->email;
        inordertrav(t->right);
    }
}

void tree::create() {
    int k = 0;
    contactNode* tmp, *p, *parent = nullptr;
    tmp = root;
    p = new contactNode();

    cout << "\nFirst Name: ";
    cin >> p->fname;
    cout << "\nLast Name: ";
    cin >> p->lname;

    do {
        cout << "\nPhone number: ";
        cin >> p->number;
        k = numchck(p->number);
    } while (k != 1);

    do {
        cout << "\nEmail-ID: ";
        cin >> p->email;
        k = mailchck(p->email);
    } while (k != 1);

    p->left = nullptr;
    p->right = nullptr;

    if (root == nullptr) {
        root = p;
    } else {
        while (tmp != nullptr) {
            parent = tmp;
            if (strcmp(p->fname, tmp->fname) < 0)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        if (strcmp(p->fname, parent->fname) < 0)
            parent->left = p;
        else
            parent->right = p;
    }
}

void tree::create2(contactNode* p) {
    contactNode* parent;
    contactNode* tmp = root;
    p->left = nullptr;
    p->right = nullptr;

    if (root == nullptr) {
        root = p;
    } else {
        while (tmp != nullptr) {
            parent = tmp;
            if (strcmp(p->fname, tmp->fname) < 0)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        if (strcmp(p->fname, parent->fname) < 0)
            parent->left = p;
        else
            parent->right = p;
    }
}

void tree::inorder() {
    inordertrav(root);
}

void tree::inordertrav(contactNode* t) {
    if (t != nullptr) {
        inordertrav(t->left);
        cout << "\nContact Details:\n";
        cout << "First name: " << t->fname << "\tLast name: " << t->lname
             << "\nPhone Number: " << t->number << "\tEmail id: " << t->email;
        inordertrav(t->right);
    }
}

contactNode* tree::minValueNode(contactNode* l) {
    contactNode* current = l;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

contactNode* tree::deleteNode(contactNode* root, char a[20]) {
    if (root == nullptr) return root;

    if (strcmp(a, root->fname) < 0)
        root->left = deleteNode(root->left, a);
    else if (strcmp(a, root->fname) > 0)
        root->right = deleteNode(root->right, a);
    else {
        if (root->left == nullptr) {
            contactNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            contactNode* temp = root->left;
            delete root;
            return temp;
        }

        contactNode* temp = minValueNode(root->right);
        root->number = temp->number;
        strcpy(root->lname, temp->lname);
        strcpy(root->fname, temp->fname);
        strcpy(root->email, temp->email);
        root->right = deleteNode(root->right, temp->fname);
    }
    return root;
}

contactNode* tree::edit(contactNode* root, char a[]) {
    if (root == nullptr) return root;

    if (strcmp(a, root->fname) < 0)
        root->left = edit(root->left, a);
    else if (strcmp(a, root->fname) > 0)
        root->right = edit(root->right, a);
    else {
        int x;
        cout << "Enter the data choice to edit:\n1.First name\t2.Last name\t3.Phone number\t4.Email id:\n";
        cin >> x;
        cout << "\nEnter the new value:";
        switch (x) {
            case 1:
                cin >> root->fname;
                break;
            case 2:
                cin >> root->lname;
                break;
            case 3:
                cin >> root->number;
                break;
            case 4:
                cin >> root->email;
                break;
            default:
                cout << "Value not modified";
        }
    }
    return root;
}

void tree::searc(contactNode* root, char a[]) {
    if (root) {
        if (strcmp(a, root->fname) < 0)
            searc(root->left, a);
        else if (strcmp(a, root->fname) > 0)
            searc(root->right, a);
        else {
            cout << "\nContact Details:\n";
            cout << "First name: " << root->fname << "\tLast name: " << root->lname
                 << "\nPhone Number: " << root->number << "\tEmail id: " << root->email;
        }
    }
}

void tree::filee(contactNode* t) {
    if (t != nullptr) {
        filee(t->left);
        outf << t->fname << " " << t->lname << " " << t->number << " " << t->email << "\n";
        filee(t->right);
    }
}

void tree::writeExisting() {
    string num, line, fname, lname, email;
    myFileStream.open("Contacts.txt");
    if (!myFileStream.is_open()) {
        cout << "File failed to open" << endl;
    }

    contactNode* tmp, *p, *parent = nullptr;
    tmp = root;

    while (getline(myFileStream, line)) {
        p = new contactNode();
        stringstream ss(line);
        getline(ss, fname, ' ');
        getline(ss, lname, ' ');
        getline(ss, num, ' ');
        p->number = atoll(num.c_str());
        getline(ss, email, ' ');

        strcpy(p->fname, fname.c_str());
        strcpy(p->lname, lname.c_str());
        strcpy(p->email, email.c_str());

        create2(p);
    }
    myFileStream.close();
}
