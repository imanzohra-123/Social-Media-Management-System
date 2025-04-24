#pragma once

#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

class Friends {
public:
    char username[50];
    char filename[64]; 
    char friendsList[50][50];
    int numFriends;

    Friends(const char* user);

    void addFriend(const char* friendUsername) {
        if (numFriends < 50) {
            strcpy_s(friendsList[numFriends], sizeof(friendsList[numFriends]), friendUsername);
            numFriends++;
            saveToFile();
        }
    }

    bool areFriends(const char* friendUsername) const {
        for (int i = 0; i < numFriends; ++i) {
            if (strcmp(friendsList[i], friendUsername) == 0) {
                return true;
            }
        }
        return false;
    }

    ~Friends() {
        saveCounterToFile();
    }

private:
    int fileCounter;

    void generateFilename() {
        sprintf_s(filename, sizeof(filename), "friends_%s_%d.dat", username, fileCounter);
    }

    void saveToFile() const {
        ofstream file(filename, ios::binary);
        for (int i = 0; i < numFriends; ++i) {
            file.write(friendsList[i], sizeof(friendsList[i]));
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file(filename, ios::binary);
        if (file) {
            int i = 0;
            while (file.read(friendsList[i], sizeof(friendsList[i]))) {
                ++i;
                if (i >= 50) break;
            }
            numFriends = i;
            file.close();
        }
    }

    void saveCounterToFile() const {
        ofstream counterFile("counter.txt");
        counterFile << fileCounter;
        counterFile.close();
    }

    void readCounterFromFile() {
        ifstream counterFile("counter.txt");
        if (counterFile) {
            counterFile >> fileCounter;
            counterFile.close();
        }
    }
};

Friends::Friends(const char* user) : numFriends(0) {
    strcpy_s(username, sizeof(username), user);
    readCounterFromFile(); 
    generateFilename(); 
    fileCounter++; 
}
