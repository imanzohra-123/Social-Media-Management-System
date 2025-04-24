#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "User.h"

using namespace std;

class Comment
{
public:
    Comment();
    ~Comment();
    void addComment(int pID, const User& user);
    void saveComment();
    void printCommentsForPostAndUser(int postID);

private:
    char comm[100];
    int postID;
    User user;
};

Comment::Comment()
{
}

Comment::~Comment()
{
}

void Comment::addComment(int pID, const User& user)
{
    cout << "Enter Comment: " << endl;

    // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string str;
    getline(cin, str);

    strncpy_s(comm, str.c_str(), sizeof(comm));
    postID = pID;
    this->user = user;
    saveComment();
}

void Comment::saveComment()
{
    ofstream file("comments.dat", ios::binary | ios::app);

    if (file)
    {
        // Serialize and write post ID
        file.write(reinterpret_cast<const char*>(&postID), sizeof(int));

        // Write comment content
        file.write(comm, sizeof(comm));

        // Serialize and write User object
        file.write(reinterpret_cast<const char*>(&user), sizeof(User));

        file.close();
    }
    else
    {
        cerr << "Error opening file for writing\n";
    }
}

void Comment::printCommentsForPostAndUser(int pID)
{
    ifstream file("comments.dat", ios::binary);

    if (file)
    {
        while (true)
        {
            file.read(reinterpret_cast<char*>(&postID), sizeof(int));

            if (file.eof())
            {
                break;
            }

            file.read(comm, sizeof(comm));

            file.read(reinterpret_cast<char*>(&this->user), sizeof(User));
            
            if (this->postID == pID)
            {
                cout << "Comment for Post ID " << postID << " by User " << user.username << ": " << comm << endl;
            }
        }

        file.close();
    }
    else
    {
        cerr << "Error opening file for reading\n";
    }
}
