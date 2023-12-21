// App.cpp
#include "App.h"
#include <iostream>

void App::run() {
    tree q;
    char a[20];
    std::string c;
    int x;
    q.writeExisting();

    do {
        std::cout << "Enter one of the following choices:\n"
                  << "1. Insert\n"
                  << "2. Delete\n"
                  << "3. Edit\n"
                  << "4. Search\n"
                  << "5. Print Phone book\n"
                  << "6. Exit\n\n";
        std::cin >> x;

        bool exiting = false;

        switch (x) {
            case 1:
                q.create();
                std::cout << "\nContact Insertion successful";
                break;
            case 2:
                std::cout << "\nEnter the First name:";
                std::cin >> a;
                q.root = q.deleteNode(q.root, a);
                std::cout << "\n1 Contact deleted successfully";
                break;
            case 3:
                std::cout << "\nEnter the First name:";
                std::cin >> a;
                q.root = q.edit(q.root, a);
                std::cout << "\nChanges updated";
                break;
            case 4:
                std::cout << "\nEnter the First name:";
                std::cin >> a;
                q.searc(q.root, a);
                break;
            case 5:
                q.inorder();
                break;
            case 6:
                exiting = true;
                break;
            default:
                std::cout << "\nOption Invalid";
                break;
        }

        if (exiting) {
            break;
        }

        q.outf.open("Data.txt", std::ios::trunc);
        q.filee(q.root);
        q.outf.close();

        std::cout << "\nContinue?\n";
        std::cin >> c;
    } while (c == "yes");

    std::cout << "\n\nTHANK YOU\nYou have Exited Successfully!\n";
}
