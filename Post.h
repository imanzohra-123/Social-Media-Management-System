#pragma once
#include <fstream>
#include <iostream>
#include "User.h"

class Post
{
public:
    Post();
    Post(User u, const char* c);
    ~Post();

    void savePost();
    static int generateUniquePostID();
    static void readLastAssignedPostID();
    static void writeLastAssignedPostID();
    void readFromFile();
    void printPostsByUser(const char* userName);

private:
    static int lastAssignedPostID;
    int postId;
    User user;
    char* content;
};

int Post::lastAssignedPostID = 0;

Post::Post() : postId(generateUniquePostID()), content(nullptr) {}

Post::Post(User u, const char* c) : postId(generateUniquePostID()), user(u) {
    size_t contentSize = strlen(c) + 1;
    content = new char[contentSize];
    strcpy_s(content, contentSize, c);
}

Post::~Post() {}

void Post::savePost() {
    ofstream file("posts.dat", ios::binary | ios::app);

    if (file) {
        file.write(reinterpret_cast<const char*>(&postId), sizeof(int));
        file.write(reinterpret_cast<const char*>(&user), sizeof(User));
        size_t contentSize = strlen(content);
        file.write(reinterpret_cast<const char*>(&contentSize), sizeof(size_t));
        file.write(content, contentSize);
        lastAssignedPostID = postId;
        writeLastAssignedPostID();
    }
    else {
        cerr << "Error opening file for writing\n";
    }
}

int Post::generateUniquePostID() {
    return ++lastAssignedPostID;
}

void Post::readLastAssignedPostID() {
    ifstream file("lastAssignedPostID.txt");
    if (file) {
        file >> lastAssignedPostID;
        file.close();
    }
}

void Post::writeLastAssignedPostID() {
    ofstream file("lastAssignedPostID.txt");
    if (file) {
        file << lastAssignedPostID;
        file.close();
    }
    else {
        cerr << "Error opening file for writing lastAssignedPostID\n";
    }
}

void Post::printPostsByUser(const char* userName) {
    ifstream file("posts.dat", ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening file for reading\n";
        return;
    }

    while (true) {
        file.read(reinterpret_cast<char*>(&postId), sizeof(int));

        if (file.eof()) {
            break;
        }

        file.read(reinterpret_cast<char*>(&user), sizeof(User));

        size_t contentSize;
        file.read(reinterpret_cast<char*>(&contentSize), sizeof(size_t));

        if (contentSize == 0 || contentSize > 10000) {
            cerr << "Invalid content size: " << contentSize << endl;
            file.seekg(contentSize, ios::cur);
            continue;
        }

        content = new (nothrow) char[contentSize + 1];

        if (!content) {
            cerr << "Error allocating memory for content\n";
            break;
        }
        file.read(content, contentSize);
        content[contentSize] = '\0';

        if (strcmp(user.username, userName) == 0) {
            cout << "Post ID " << postId << " by " << userName << ": " << content << endl;
        }

        delete[] content;
    }

    file.close();
}

void Post::readFromFile() {
    ifstream file("posts.dat", ios::binary);

    if (file) {
        file.read(reinterpret_cast<char*>(&postId), sizeof(int));
        file.read(reinterpret_cast<char*>(&user), sizeof(User));

        size_t contentSize;
        file.read(reinterpret_cast<char*>(&contentSize), sizeof(size_t));

        char* contentBuffer = new char[contentSize + 1];
        file.read(contentBuffer, contentSize);

        contentBuffer[contentSize] = '\0';
        content = contentBuffer;

        delete[] contentBuffer;
    }
    else {
        cerr << "Error opening file for reading\n";
    }
}
