# Phone Book Management System

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Installation](#installation)
- [Dependencies](#dependencies)
- [File Structure](#file-structure)
- [Contributing](#contributing)
- [License](#license)

## Introduction
This project implements a Phone Book Management System using C++. It allows users to perform basic operations such as adding, deleting, editing, searching, and printing contacts in a phone book.

## Features
- Insert new contacts
- Delete existing contacts
- Edit contact information
- Search for contacts
- Print the phone book
- Interactive command-line interface

## Usage
1. Compilation:
 - Compile the project using the provided Makefile.
	
 	make

2. Running the Program:
 - Execute the compiled program.
	
 	./PHONEBOOK_MANAGEMENT_SYSTEM

3. Cleaning Up
 - To clean up the generated files, run:
	
 	make clean

## Installation
Clone the repository to your local machine:

	git clone https://github.com/Krishna-Kannoj/PHONEBOOK_MANAGEMENT_SYSTEM.git
	cd PHONEBOOK_MANAGEMENT_SYSTEM/ 

## Dependencies
 - This project uses C++11 standard.
 - Ensure a compatible C++ compiler (e.g., g++) is installed.

## File Structure
	PHONEBOOK_MANAGEMENT_SYSTEM/
	|-- src/
	|   |-- App.cpp      # Implementation of the main application class
	|   |-- contactNode.cpp  # Implementation of the contactNode class
	|   |-- main.cpp     # Main entry point of the program
	|   |-- tree.cpp     # Implementation of the tree class
	|-- include/
	|   |-- App.h        # Declaration of the main application class
	|   |-- contactNode.h    # Declaration of the contactNode class
	|   |-- tree.h       # Declaration of the tree class
	|-- Makefile        # Makefile for building the project
	|-- README.md       # Project documentation

  1. App.cpp: Implementation of the main application class.
   - Responsible for handling user input and interacting with the tree class.
   - Contains the run function, which orchestrates the main functionality of the program.
  2. contactNode.cpp: Implementation of the contactNode class.
   - Defines the structure and behavior of a node in the binary search tree.
   - Manages contact information, such as first name, last name, phone number, and email.
   - Implements functions like minValueNode for finding the node with the minimum value.
  3. main.cpp: Main entry point of the program.
   - Contains the main function where the program execution begins.
   - Calls the App::run function to initiate the phone book management system.
  4. tree.cpp: Implementation of the tree class.
   - Defines a binary search tree to store and manage contact nodes.
   - Includes functions for creating nodes, inserting nodes, deleting nodes, searching for nodes, and editing nodes.
  5. App.h: Declaration of the main application class.
   - Declares the App class with its member functions and variables.
  6. contactNode.h: Declaration of the contactNode class.
   - Declares the contactNode class with its member variables and functions.
  7. tree.h: Declaration of the tree class.
   - Declares the tree class with its member functions and variables.

## Contributing
- Feel free to contribute to this project by forking it and creating a pull request with any improvements or features.

## License
 - This project is licensed under the MIT License.


