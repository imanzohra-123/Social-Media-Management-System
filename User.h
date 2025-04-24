// User.h
#pragma once

#include <fstream>
#include <string>
using namespace std;

class User {
public:
    char username[50];
    char password[50];
    char email[50]; 
    char birthdate[20];

    User();

    void saveToFile() const {
        ofstream file("users.dat", ios::binary | ios::app);

        if (file) {
            file.write(username, sizeof(username));
            file.write(password, sizeof(password));
            file.write(email, sizeof(email));
            file.write(birthdate, sizeof(birthdate));
            file.close();
        }
    }

    static User loadFromFile(const char* username) {
        ifstream file("users.dat", ios::binary);
        User temp;

        while (file.read(temp.username, sizeof(temp.username)) &&
            file.read(temp.password, sizeof(temp.password)) &&
            file.read(temp.email, sizeof(temp.email)) &&
            file.read(temp.birthdate, sizeof(temp.birthdate))) {
            if (strcmp(temp.username, username) == 0) {
                file.close();
                return temp;
            }
        }

        file.close();
        return User();
    }
    void updateInfo(const char* newUsername, const char* newPass, const char* newEmail, const char* newBirthdate) {
       
        strncpy_s(email, sizeof(email), newEmail, _TRUNCATE);
        strncpy_s(birthdate, sizeof(birthdate), newBirthdate, _TRUNCATE);

        fstream file("users.dat", ios::binary | ios::in | ios::out);

        if (file) {
            User temp;

            while (file.read(reinterpret_cast<char*>(&temp), sizeof(User))) {
                if (strcmp(temp.username, username) == 0) {
                    // Found the user, update the information
                    file.seekp(file.tellg() - static_cast<streamoff>(sizeof(User)));
                    strncpy_s(temp.username, sizeof(temp.username), newUsername, _TRUNCATE);
                    strncpy_s(temp.password, sizeof(temp.password), newPass, _TRUNCATE);
                    strncpy_s(temp.email, sizeof(temp.email), email, _TRUNCATE);
                    strncpy_s(temp.birthdate, sizeof(temp.birthdate), birthdate, _TRUNCATE);
                    file.write(reinterpret_cast<const char*>(&temp), sizeof(User));
                    break;
                }
            }

            file.close();
        }
    }


};

User::User()
{

}
