# include <string>
# include <stdexcept>
# include "Tag.h"

using std::string, std::vector;

Tag::Tag(string tagName) : tagName(tagName), tagPosts(0) {
        if (tagName.length() < 2 || tagName.at(0) != '#' || !isalpha(tagName.at(1)) ||
        tagName.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
        { throw std::invalid_argument("Your tagname is bums");}
    
    for (unsigned int i = 0; i < tagName.length(); ++i){
        char char_at_i = tagName[i];
        if (char_at_i == '!' || char_at_i == ',' || char_at_i == '.' || char_at_i == '?'){
            ++i;
            if (i == tagName.length()) continue;
            char_at_i = tagName[i];
            if (char_at_i == '!' || char_at_i == ',' || char_at_i == '.' || char_at_i == '?'){
                throw std::invalid_argument("Your tagname is bums");
            }
        }
    }
}

string Tag::getTagName() {
    return tagName;
}

vector<Post*>& Tag::getTagPosts() {
    return tagPosts;
}

void Tag::addTagPost(Post* post) {
    if(post == nullptr) throw std::invalid_argument("Bro the post is nullptr");
    tagPosts.push_back(post);
}
