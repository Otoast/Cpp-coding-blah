# include <iostream>
# include <string>
# include <stdexcept>
# include "Post.h"

using std::string, std::vector;

Post::Post(unsigned int postId, string userName, string postText) : postId(postId), userName(userName), postText(postText) {
    if (postId == 0 || userName.empty() || postText.empty()) {
        throw std::invalid_argument("post constructor: invalid parameter values");
    }
}

unsigned int Post::getPostId() {
    return postId;
}

string Post::getPostUser() {
    return userName;
}

string Post::getPostText() {
    return postText;
}

vector<string> Post::findTags() {
    vector <string> allTags;
    for (unsigned int i = 0; i < postText.length(); ++i){
        string tagFound = "";
        if (postText.at(i) == '#'){
            while (i < postText.length() && postText.at(i) != ' '){ 
                tagFound += tolower(postText.at(i++));
                }
            int tagIndex = tagFound.length() - 1;
            while (tagIndex > 0 && !isalnum(tagFound.at(tagIndex))){
                tagFound.pop_back();
                --tagIndex;
            }

            bool uniqueTag = true;
            for (string tag : allTags){
                if (tagFound == tag) uniqueTag = false;
            }
            if (uniqueTag) allTags.push_back(tagFound);
        }   
    
    }

    return allTags;
}
