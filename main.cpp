#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Person {
protected:
    int id;
    string name;

public:
    Person(int id, string name) : id(id), name(name) {}

    int getId() const { return id; }
    string getName() const { return name; }
};

class Book {
private:
    int id;
    string title;
    string author;
    int availableCopies;

public:
    Book(int id, string title, string author, int copies)
        : id(id), title(title), author(author), availableCopies(copies) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getAvailableCopies() const { return availableCopies; }

    void displayInfo() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author
                  << ", Available Copies: " << availableCopies << endl;
    }

    void updateAvailability(int count) {
        availableCopies += count;
    }
};

class User : public Person {
private:
    vector<Book*> borrowedBooks;

public:
    User(int id, string name) : Person(id, name) {}

    void borrowBook(Book* book) {
        if (book->getAvailableCopies() > 0) {
            borrowedBooks.push_back(book);
            book->updateAvailability(-1);
            cout << "Book borrowed successfully." << endl;
        } else {
            cout << "No copies available to borrow." << endl;
        }
    }

    void returnBook(Book* book) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), book);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            book->updateAvailability(1);
            cout << "Book returned successfully." << endl;
        } else {
            cout << "Book not found in borrowed list." << endl;
        }
    }
};

class Library {
private:
    unordered_map<int, Book*> books;
    vector<User*> users;

public:
    void addBook(Book* book) {
        books[book->getId()] = book;
        cout << "Book added successfully." << endl;
    }

    void removeBook(int id) {
        books.erase(id);
        cout << "Book removed successfully." << endl;
    }

    void registerUser(User* user) {
        users.push_back(user);
        cout << "User registered successfully." << endl;
    }

    void loanBook(int bookId, int userId) {
        if (books.find(bookId) != books.end()) {
            for (User* user : users) {
                if (user->getId() == userId) {
                    user->borrowBook(books[bookId]);
                    return;
                }
            }
            cout << "User not found." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    void returnBook(int bookId, int userId) {
        if (books.find(bookId) != books.end()) {
            for (User* user : users) {
                if (user->getId() == userId) {
                    user->returnBook(books[bookId]);
                    return;
                }
            }
            cout << "User not found." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    void viewAllBooks() const {
        for (const auto& [id, book] : books) {
            book->displayInfo();
        }
    }
};

void displayMenu() {
    cout << "\nLibrary Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Register User" << endl;
    cout << "3. Loan Book" << endl;
    cout << "4. Return Book" << endl;
    cout << "5. View All Books" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    Library library;

    while (true) {
        displayMenu();
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, copies;
            string title, author;
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);
            cout << "Enter Available Copies: ";
            cin >> copies;
            Book* newBook = new Book(id, title, author, copies);
            library.addBook(newBook);
        } else if (choice == 2) {
            int id;
            string name;
            cout << "Enter User ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter User Name: ";
            getline(cin, name);
            User* newUser = new User(id, name);
            library.registerUser(newUser);
        } else if (choice == 3) {
            int bookId, userId;
            cout << "Enter Book ID to Loan: ";
            cin >> bookId;
            cout << "Enter User ID: ";
            cin >> userId;
            library.loanBook(bookId, userId);
        } else if (choice == 4) {
            int bookId, userId;
            cout << "Enter Book ID to Return: ";
            cin >> bookId;
            cout << "Enter User ID: ";
            cin >> userId;
            library.returnBook(bookId, userId);
        } else if (choice == 5) {
            cout << "Library Inventory:" << endl;
            library.viewAllBooks();
        } else if (choice == 6) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
