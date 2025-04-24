#pragma once

#include <fstream>

class Likes
{
public:
    Likes();
    ~Likes();

    void likePost(int postID);
    void viewAllLikes(int postID);

private:
    int pID;
    int likes;

    int findPostIndex(int postID);
};

Likes::Likes() {}

Likes::~Likes() {}

void Likes::likePost(int postID)
{
    fstream file("likes.dat", ios::binary | ios::in | ios::out);

    if (file.is_open()) {
        int index = findPostIndex(postID);

        if (index != -1) {
            file.seekp(index * sizeof(Likes) + offsetof(Likes, likes), ios::beg);
            file.read(reinterpret_cast<char*>(&likes), sizeof(likes));
            likes++;
            file.seekp(index * sizeof(Likes) + offsetof(Likes, likes), ios::beg);
            file.write(reinterpret_cast<const char*>(&likes), sizeof(likes));
            cout << "Post with ID " << postID << " liked. Total likes: " << likes << endl;
        }
        else {
            Likes newEntry;
            newEntry.pID = postID;
            newEntry.likes = 1;
            file.seekp(0, ios::end);
            file.write(reinterpret_cast<const char*>(&newEntry), sizeof(Likes));
            cout << "New post with ID " << postID << " added. Total likes: 1\n";
        }

        file.close();
    }
    else {
        cerr << "Error opening file for reading and writing.\n";
    }
}

void Likes::viewAllLikes(int postID)
{
    ifstream file("likes.dat", ios::binary);

    if (file.is_open()) {
        int index = findPostIndex(postID);

        if (index != -1) {
            file.seekg(index * sizeof(Likes), ios::beg);
            file.read(reinterpret_cast<char*>(this), sizeof(Likes));
            cout << "Post with ID " << postID << " has " << likes << " likes.\n";
        }
        else {
            cerr << "Post with ID " << postID << " not found.\n";
        }

        file.close();
    }
    else {
        cerr << "Error opening file for reading.\n";
    }
}

int Likes::findPostIndex(int postID)
{
    ifstream file("likes.dat", ios::binary);

    if (file.is_open()) {
        int index = 0;
        while (file.read(reinterpret_cast<char*>(this), sizeof(Likes))) {
            if (pID == postID) {
                file.close();
                return index;
            }
            index++;
        }

        file.close();
    }
    else {
        cerr << "Error opening file for reading.\n";
    }

    return -1; // Post not found
}
