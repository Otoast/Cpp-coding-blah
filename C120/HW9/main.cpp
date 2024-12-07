# include <iostream>
# include <string>
# include <stdexcept>
# include "Network.h"

using std::cout, std::cin, std::endl, std::string, std::vector;

void printMenu() {
    cout << "Welcome to CPPeers" << endl;
    cout << "The options are: " << endl;
    cout << "1. load data file and add information" << endl;
    cout << "2. show posts by user" << endl;
    cout << "3. show posts with hashtag" << endl;
    cout << "4. show most popular hashtag" << endl;
    cout << "9. quit" << endl;
    cout << "--------> Enter your option: ";
}

void processLoad(Network& cppeers) {
    string fileName = "";
    cout << "Enter filename: ";
    cin >> fileName;
    cppeers.loadFromFile(fileName);
}

void processPostsByUser(Network& cppeers) {
    cout << "Enter username: ";
    string userName = ""; 
    cin >> userName;
    vector <Post*> userPosts = cppeers.getPostsByUser(userName);
    for (Post* post : userPosts) cout << post->getPostText() << endl;
}

void processPostsWithHashtags(Network& cppeers) {
    cout << "Enter tagname: ";
    string tagName = "";
    cin >> tagName;

    vector <Post*> postsWithTag = cppeers.getPostsWithTag(tagName);
    for (Post *post : postsWithTag) cout << post->getPostText() << endl;

}

void processMostPopularHashtag(Network& cppeers) {
    vector<string> mostPop = cppeers.getMostPopularHashtag();
    for (unsigned int i = 0; i < mostPop.size(); ++i){
        cout << mostPop.at(i) << endl;
    }
}

int main() {

    try {
        Network cppeers;

        int choice = 0;

        do {
            printMenu();
            cin >> choice;
            switch(choice) {
                case 1: {
                    processLoad(cppeers);
                    break;
                }
                case 2: {
                    processPostsByUser(cppeers);
                    break;
                }
                case 3: {
                    processPostsWithHashtags(cppeers);
                    break;
                }
                case 4: {
                    processMostPopularHashtag(cppeers);
                    break;
                }
            }
        } while (choice != 9);
    } catch (std::exception& exc) {
        std::cout << exc.what() << endl;
    }

    return 0;
}
