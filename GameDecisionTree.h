#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"

template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;
public:
    GameDecisionTree() : root(nullptr) {}

    // Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const string& filename, char delimiter) {
        vector<Node<Story> > tempList;
        std::ifstream storyFile(filename);
        if(!storyFile.is_open()) {
            std::cout << "Error: storyFile failed to open" << std::endl;
            return;
        }

        // Build tree
        std::string line;
        while(getline(storyFile, line)) {
            string eventNumber;
            string description;
            string leftEventNumber;
            string rightEventNumber;

            // Parse lines
            std::stringstream lineStream(line);
            getline(lineStream, eventNumber, delimiter);
            getline(lineStream, description, delimiter);
            getline(lineStream, leftEventNumber, delimiter);
            getline(lineStream, rightEventNumber, delimiter);

            // Create vector of story data object
            Story tempStory(description, std::stoi(eventNumber), std::stoi(leftEventNumber), std::stoi(rightEventNumber));
            Node<Story> tempNode(tempStory);
            tempList.push_back(tempNode);
        }

        // REMOVE TEST LATER
        for(int i = 0; i < tempList.size(); i++) {
            std::cout << tempList[i].data.eventNumber << tempList[i].data.description << tempList[i].data.leftEventNumber << tempList[i].data.rightEventNumber << std::endl;
        }
    }

    // Function to start the game and traverse the tree based on user input
    void playGame() {

    }
};

#endif // GAMEDECISIONTREE_H
