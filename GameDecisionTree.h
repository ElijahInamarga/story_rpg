#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"
#include <vector>

template <typename T>
class GameDecisionTree {
private:
    Node<T>* rootPtr;
public:
    GameDecisionTree() : rootPtr(nullptr) {}

    void treeify(std::vector<Node<T>>* vectorPtr, Node<T>* nodePtr) {
        int leftIndex = nodePtr->data.leftEventNumber - 1;
        int rightIndex = nodePtr->data.rightEventNumber - 1;

        // Base case 1
        if(leftIndex >= vectorPtr->size() || leftIndex < 0) {
            return;
        }

        Node<T>* leftChild = &(*vectorPtr)[leftIndex];
        nodePtr->left = leftChild;
        treeify(vectorPtr, leftChild);
        // Base case 2
        if(rightIndex >= vectorPtr->size() || rightIndex < 0) {
            return;
        }
        
        Node<T>* rightChild = &(*vectorPtr)[rightIndex];
        nodePtr->right = rightChild;
        treeify(vectorPtr, rightChild);
    }

    // Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const string& filename, char delimiter) {
        std::vector<Node<T>> tempList;
        std::ifstream storyFile(filename);
        if(!storyFile.is_open()) {
            std::cout << "Error: storyFile failed to open" << std::endl;
            return;
        }

        // Build vector of story data object
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

            Story tempStory(description, std::stoi(eventNumber), std::stoi(leftEventNumber), std::stoi(rightEventNumber));
            Node<Story> tempNode(tempStory);
            tempList.push_back(tempNode);
        }
        storyFile.close();

        // REMOVE TEST LATER
        // for(int i = 0; i < tempList.size(); i++) {
        //     std::cout << tempList[i].data.eventNumber << tempList[i].data.description << tempList[i].data.leftEventNumber << tempList[i].data.rightEventNumber << std::endl;
        // }

        // Convert vector into binary tree
        rootPtr = &(tempList[0]); // Tree starts with vector[0]
        treeify(&tempList, rootPtr);
    }

    // Function to start the game and traverse the tree based on user input
    void playGame() {
        std::cout << rootPtr->data.description << std::endl;
    }
};

#endif // GAMEDECISIONTREE_H
