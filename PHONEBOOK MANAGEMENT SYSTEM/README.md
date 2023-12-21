Phone Book Management System
This application is a simple phone book management system implemented in C++ to manage contacts efficiently.

 - Table of Contents
 - Introduction
 - Features
 - Usage
 - Installation
 - Dependencies
 - File Structure
 - Contributing
 - License

Introduction
 - The Phone Book Management System is designed to handle contact information efficiently. It allows users to add, delete, edit, search, and display contact details through an intuitive command-line interface.

Features
 - Create Contacts: Add new contacts with details including first name, last name, phone number, and email.
 - Delete Contacts: Remove contacts by providing the first name.
 - Edit Contacts: Modify existing contact information such as first name, last name, phone number, or email.
 - Search Contacts: Find contacts by providing the first name.
 - Display Contacts: View all contacts stored in the phone book.

Usage

1. Compilation:
 - Compile the project using the provided Makefile.
	make

2. Running the Program:
 - Execute the compiled program.
	./PHONEBOOK_MANAGEMENT_SYSTEM

3. Cleaning Up
 - To clean up the generated files, run:
	make clean

Installation
Clone the repository to your local machine:

	git clone https://github.com/Krishna-Kannoj/PHONEBOOK_MANAGEMENT_SYSTEM.git
	cd PHONEBOOK_MANAGEMENT_SYSTEM/ 

Dependencies
 - This project uses C++11 standard.
 - Ensure a compatible C++ compiler (e.g., g++) is installed.

File Structure
 - main.cpp: Contains the main program logic and user interaction.
 - tree.cpp and tree.h: Implement the tree structure for managing contacts.
 - contactNode.cpp and contactNode.h: Define the contactNode class for individual contact details.
 - view.cpp and view.h: Handle user interface and output display functionalities.
 - Makefile: Automates the compilation process.

Contributing
 - Feel free to contribute to this project by forking it and creating a pull request with any improvements or features.

License
 - This project is licensed under the MIT License.

