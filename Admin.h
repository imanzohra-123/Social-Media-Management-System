
#pragma once
#include "User.h"
#include <iostream>
#include <cstring>
using namespace std;

class Admin : public User {
public:
    Admin();
    ~Admin();
    void login();
    void addUser();
    void deleteUser(const char* usernameToDelete);
    void viewAllUsers();
private:
};

Admin::Admin() {
}

Admin::~Admin() {
}

void Admin::login() {
    // Basic login implementation
    char inputUsername[50];
    char inputPassword[50];

    cout << "Enter username: ";
    cin >> inputUsername;

    cout << "Enter password: ";
    cin >> inputPassword;

    if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
        cout << "Login successful. Welcome, Admin!" << endl;
    }
    else {
        cout << "Login failed. Incorrect username or password." << endl;
    }
}

void Admin::addUser() {
    cout << "User added successfully!" << endl;
}

void Admin::deleteUser(const char* usernameToDelete) {
    cout << "User deleted successfully!" << endl;
}

void Admin::viewAllUsers() {
    cout << "List of all users:" << endl;
}

int main() {
    Admin admin;
    admin.login();

    admin.addUser();
    admin.viewAllUsers();
    admin.deleteUser("usernameToDelete");

    return 0;
}
