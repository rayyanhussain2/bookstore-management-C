# Online Bookstore Management System - C Project

## Overview

This project is a C implementation of an Online Bookstore Management System, developed as part of the Data Structure and Algorithms course (CSE 102) at Indraprastha Institute of Information Technology, Delhi, for the Academic Year 2022 - 23. The main objective of this project was to apply the knowledge gained in the course to create a functional and efficient system that can handle a large number of books using appropriate data structures and algorithms.

## Features

- **Data Structure Selection**: The project utilizes AVL trees for the backend to efficiently store and manage different books. This ensures quick searching and sorting operations.

- **File I/O**: The system implements functionality to read book information from a file at the start of the program and updates the file with changes made during the program execution. This ensures that the bookstore inventory is persistent across sessions.

- **Searching**: The searching functionality is based on AVL tree search, enabling fast and efficient search operations.

- **Book Operations**: The system supports various book operations such as adding a new book, deleting an existing book, updating the number of available book copies, and maintaining book availability.

- **User Interface**: Although there were initial plans to use a front-end library like GTK+ or raygui, due to time constraints, the project is currently terminal-based, providing a simple text-based interface for users.

- **Error Handling**: The project implements proper error handling mechanisms to manage scenarios such as invalid user inputs, book not found, out-of-stock books, and file read/write errors. This ensures smooth and reliable functioning of the system.

- **Efficiency Optimization**: The project focuses on efficiency optimization to minimize time complexity for critical operations. AVL trees offer a logarithmic time complexity for insertion, searching, and deletion, ensuring optimal performance even with a large number of books.

- **Modular Code Structure**: The codebase is organized into different appropriate modules and header files, promoting a clean and maintainable code structure.

- **Custom fgetStdin Function**: The project includes a custom fgetStdin function, allowing the program to know the current first character of the buffer, enhancing input processing capabilities.

- **Clean Code**: One of the primary goals of the project was to write clean and readable code, ensuring easy comprehension and future maintainability.

- **Responsibility of Clearing Buffer**: A standard is maintained throughout the codebase, where clearing the buffer is the responsibility of the caller.

## Possible Improvements

While the current version of the Online Bookstore Management System is functional and efficient, there are some areas where further improvements could be made:

- **Check for Conflicting Names/ISBN**: Adding a feature to check for existing conflicting names or ISBNs would enhance data integrity and prevent duplicates in the bookstore inventory.

- **Encryption and Decryption of Files**: Implementing file encryption and decryption mechanisms would provide an added layer of security for the sensitive information stored in the files.

- **Sorting While Listing**: Implementing sorting algorithms while listing books would improve the user experience by presenting the books in a more organized manner.

- **Sorting According to Parameters**: Adding the ability to sort books based on various parameters like author, ISBN, etc., would further enhance the system's functionality and usability.

## Usage

To use the Online Bookstore Management System, follow these steps:

1. Clone the repository to your local machine.

2. Compile the C source code using a C compiler.

3. Run the compiled executable to launch the terminal-based user interface.

4. Use the provided commands to browse, search, and perform various book operations.

## License

This project is provided under the [MIT License](LICENSE), allowing users to freely use, modify, and distribute the code, with appropriate attribution to the original author.

## Contributions

Contributions to the project are welcome! If you find any issues or have ideas for enhancements, feel free to submit a pull request or open an issue on the GitHub repository.

## Acknowledgments

Special thanks to the instructors and faculty of the Data Structure and Algorithms course (CSE 102) at Indraprastha Institute of Information Technology, Delhi, for their guidance and support during the development of this project.

## Contact

For any further information or inquiries, please feel free to contact the project maintainer:

[Your Name]
[Your Email Address]
[Your GitHub Profile]
