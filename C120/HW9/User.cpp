# include <string>
# include <stdexcept>
# include "User.h"
# include <iostream>
using std::string, std::vector;

User::User(string userName) : userName(userName), userPosts(0){
    if (userName.empty() || !islower(userName.at(0)) || 
        userName.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
        { 
            throw std::invalid_argument("Invalid username. CHECK THE RULES"); }

}

string User::getUserName() {
    return userName;
}

vector<Post*>& User::getUserPosts() {
    return userPosts;
}

void User::addUserPost(Post* post) {
    if (post == nullptr) throw std::invalid_argument("Why'd you try to add an empty post.");
    (this->userPosts).push_back(post);
}
