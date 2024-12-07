# include <iostream>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include "Network.h"

using std::string, std::vector;
using std::cout, std::endl;
Network::Network() : users({}), posts({}), tags({}) {}

void Network::loadFromFile(string fileName) {
    std::ifstream inFS (fileName);
    if (!inFS.is_open()) throw std::invalid_argument("File can't be opened.");
    string fileLine;
    std::getline(inFS, fileLine);
    string firstWord, postText, userName, postId;
    try{ 
        while (!inFS.eof()){
        
                std::stringstream ioSS (fileLine);
                ioSS >> firstWord;
                if (firstWord == "User"){
                    ioSS >> userName;
                    Network::addUser(userName);
                }
                else if (firstWord == "Post"){
                    ioSS >> postId;
                    if (postId.find_first_not_of("1234567890") != string::npos){
                        throw std::invalid_argument("Issue with postId: " + postId);
                    }
                    ioSS >> userName;   ioSS.get();
                    getline(ioSS, postText); 
                    Network::addPost(stoi(postId), userName, postText);
                }
                else{
                    throw std::runtime_error("First word neither User or Post");
                }
                std::getline(inFS, fileLine);
            
        }
    }
    catch(std::exception &e){
        throw std::runtime_error("IDK");
        }


}

void Network::addUser(string userName) {
    for (unsigned int i = 0; i < users.size(); ++i){
        string userName_toCheck = users.at(i)->getUserName();
        string userName_A = "", userName_B = "";
        for (char c : userName_toCheck){
            userName_A += tolower(c);
        }
        for (char c : userName){
            userName_B += tolower(c);
        }
        if (userName_A == userName_B)
            { throw std::invalid_argument("Username is already in use."); }

    }
    users.push_back(new User(userName));
    std::cout << "Added User " << userName << std::endl;

}

void Network::addPost(unsigned int postId, string userName, string postText) {
    string postID = std::to_string(postId);
    if (postID.find_first_not_of("1234567890") != string::npos){
            throw std::invalid_argument("Issue with postId: " + postId);
            }
    bool userNameFound = false;
    int indexFound = -1;
    for (unsigned int i = 0; i < users.size(); ++i){
        string userName_A = "";
        string userName_B = "";
        for (char c : users.at(i)->getUserName()){
            userName_A += tolower(c);
        }
        for (char c : userName){
            userName_B += tolower(c);
        }
        if (userName_A == userName_B)
            {
                userNameFound = true;
                indexFound = i;
                break;
            }
    }

    if (!userNameFound) throw std::invalid_argument("Username does not exist.");
    vector <Post*> userPosts = getPostsByUser(userName);
    for (Post *post : userPosts){
        if (post->getPostId() == postId) throw std::invalid_argument("Duplicate post.");
    }

    Post *newPost = new Post(postId, userName, postText);

    users.at(indexFound)->addUserPost(newPost);   posts.push_back(newPost);
    vector <string> allTags = newPost->findTags();
    for (string tagName : allTags){
        bool tagExists = false;
        for (Tag *tag : tags){
            if (tag->getTagName() == tagName) 
            {   
                tagExists = true; tag->addTagPost(newPost);
                break;
            }
        }
        if (!tagExists){
            try {
                Tag *newTag = new Tag(tagName);
                newTag->addTagPost(newPost);
                tags.push_back(newTag);   
            }
            catch(std::invalid_argument &e){}
        }

    }
    std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
    bool userNameFound = false;
    int indexFound = -1;
    if (userName.empty()) throw std::invalid_argument("Username is empty.");
    for (unsigned int i = 0; i < users.size(); ++i){
        string userName_A = "";
        string userName_B = "";
        for (char c : users.at(i)->getUserName()){
            userName_A += tolower(c);
        }
        for (char c : userName){
            userName_B += tolower(c);
        }
        if (userName_A == userName_B)
            {
                userNameFound = true;
                indexFound = i;
                break;
            }
    }
    if (!userNameFound) throw std::invalid_argument("Username not found.");
    return users.at(indexFound)->getUserPosts();
}

vector<Post*> Network::getPostsWithTag(string tagName) {
    if (tagName == "") throw std::invalid_argument("Tag is empty");
    for (Tag *tag : tags){
        if (tag->getTagName() == tagName){
            return tag->getTagPosts();
        }
    }
    throw std::invalid_argument("Tag cannot be found.");
}

vector<string> Network::getMostPopularHashtag() {
    vector<int> tagFrequency;
    vector<string> mostPopular_hashtags(0);
    for (Tag *tag : tags){
        tagFrequency.push_back((tag->getTagPosts()).size());
    }
    int mostFrequent_Amt = INT32_MIN;
    for (unsigned int i = 0; i < tagFrequency.size(); ++i){
        if (tagFrequency.at(i) > mostFrequent_Amt){
            mostFrequent_Amt = tagFrequency.at(i);
        }
    }
    for (unsigned int i = 0; i < tagFrequency.size(); ++i){
        if (tagFrequency.at(i) == mostFrequent_Amt){
            mostPopular_hashtags.push_back(tags.at(i)->getTagName());
        }
    }
    return mostPopular_hashtags;

}

Network::~Network() {
    for (unsigned int i = 0; i < users.size(); ++i) {
        delete users.at(i);
    }

    for (unsigned int i = 0; i < tags.size(); ++i) {
        delete tags.at(i);
    }
    
    for (unsigned int i = 0; i < posts.size(); ++i) {
        delete posts.at(i);
    }
}
