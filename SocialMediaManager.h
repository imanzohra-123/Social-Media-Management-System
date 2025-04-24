#pragma once

#include "Post.h"  // Assuming you have a Post class defined
#include "Comments.h"
#include "Friend.h"
#include "Likes.h"

class SocialMediaManagement {
public:
    SocialMediaManagement();
    ~SocialMediaManagement();

    void registerUser();
    bool loginUser();
    void createPost();
    void printPosts();
    void addComment();
    void printAllComments();
    void addFriend();
    bool checkIfFriends();
    void updateInfo();
    void likePost();
    void viewLikes();


private:
    User currentUser;
};

SocialMediaManagement::SocialMediaManagement() {
}

SocialMediaManagement::~SocialMediaManagement() {
}

void SocialMediaManagement::registerUser() {
    User newUser;

    cout << "Enter username: ";
    cin >> newUser.username;

    cout << "Enter password: ";
    cin >> newUser.password;
    cout << "Enter email: ";
    cin >> newUser.email;
    cout << "Enter birthdate: ";
    cin >> newUser.birthdate;

    newUser.saveToFile();
    cout << "Registration successful!\n";
}

bool SocialMediaManagement::loginUser() {
    char inputUsername[50];
    char inputPassword[50];

    cout << "Enter username: ";
    cin >> inputUsername;

    cout << "Enter password: ";
    cin >> inputPassword;

    User loadedUser = User::loadFromFile(inputUsername);

    if (strcmp(loadedUser.password, inputPassword) == 0) {
        currentUser = loadedUser;  // Update currentUser only if login is successful
        cout << "Login successful!\n";
        return true;
    }
    else {
        cout << "Login failed. Incorrect username or password.\n";
        return false;
    }
    return false;
}

void SocialMediaManagement::createPost()
{
    cout << "Enter Content: " << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char tempCon[100];
    string str;
    getline(cin, str);

    strncpy_s(tempCon, str.c_str(), sizeof(tempCon));

    Post tempPost(currentUser, tempCon);
    tempPost.savePost();
}

void SocialMediaManagement::printPosts()
{
    Post p;
    p.printPostsByUser(currentUser.username);

}

void SocialMediaManagement::addComment()
{
    Comment c;
    int pID;
    cout << "Enter Post ID: ";
    cin >> pID;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    c.addComment(pID, currentUser);
    return;
}

void SocialMediaManagement::printAllComments()
{
    Comment c;
    cout << "Enter Post ID: ";
    int pID;
    cin >> pID;
    c.printCommentsForPostAndUser(pID);
    return;
}

void SocialMediaManagement::addFriend()
{
    Friends f(currentUser.username);
    

    cout << "Enter the username of the user you want to add as a friend" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    char tempCon[100];
    string str;
    getline(cin, str);

    strncpy_s(tempCon, str.c_str(), sizeof(tempCon));
    f.addFriend(tempCon);
    
}

bool SocialMediaManagement::checkIfFriends()
{
    cout << "Enter username: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    char tempCon[100];
    string str;
    getline(cin, str);

    strncpy_s(tempCon, str.c_str(), sizeof(tempCon));
    Friends f(tempCon);
    Friends f2(currentUser.username);
    if (f.areFriends(currentUser.username) || f2.areFriends(tempCon))
    {
        cout << "The users are friends" << endl;
        return true;
    }
    cout << "The users are not friends" << endl;
    return false;
}

void SocialMediaManagement::updateInfo()
{
    User newUser;

    cout << "Enter username: ";
    cin >> newUser.username;

    cout << "Enter password: ";
    cin >> newUser.password;
    cout << "Enter email: ";
    cin >> newUser.email;
    cout << "Enter birthdate: ";
    cin >> newUser.birthdate;
    cout << "Enter the new Info:" << endl;

    currentUser.updateInfo(newUser.username, newUser.password, newUser.email, newUser.birthdate);
    cout << "Information Updated Successfully." << endl;
}

void SocialMediaManagement::likePost()
{
    cout << "Enter Post ID: ";
    int n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> n;
    Likes l;
    l.likePost(n);
}
void SocialMediaManagement::viewLikes()
{
    cout << "Enter Post ID: ";
    int n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> n;
    Likes l;
    l.viewAllLikes(n);
}
