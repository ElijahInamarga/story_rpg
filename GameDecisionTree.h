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
    std::vector<Node<T>> tempList;
public:
    GameDecisionTree() : rootPtr(nullptr) {}

    void treeify(Node<T>* nodePtr) {
        int leftIndex = nodePtr->data.leftEventNumber - 1;
        int rightIndex = nodePtr->data.rightEventNumber - 1;

        // Base case 1
        if(leftIndex >= tempList.size() || leftIndex < 0) {
            return;
        }

        Node<T>* leftChild = &tempList[leftIndex];
        nodePtr->left = leftChild;
        treeify(leftChild);

        // Base case 2
        if(rightIndex >= tempList.size() || rightIndex < 0) {
            return;
        }
        
        Node<T>* rightChild = &tempList[rightIndex];
        nodePtr->right = rightChild;
        treeify(rightChild);
    }

    // Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const std::string& filename, char delimiter) {
        std::ifstream storyFile(filename);
        if(!storyFile.is_open()) {
            std::cout << "Error: storyFile failed to open!" << std::endl;
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

        // Convert vector into binary tree
        rootPtr = &(tempList[0]); // Tree starts with vector[0]
        treeify(rootPtr);
    }

    // Function to start the game and traverse the tree based on user input
    void playGame() {
        Node<T>* currentPtr = rootPtr;
        while(true) {
            int choice;
            std::cout << currentPtr->data.description << std::endl;

            // Game ends when there are no more choices
            if(currentPtr->data.leftEventNumber == -1 && currentPtr->data.rightEventNumber == -1) 
                return;

            // If user has 2 choices
            if(currentPtr->data.leftEventNumber != -1 && currentPtr->data.rightEventNumber != -1) {
                cin >> choice;
                if(choice == 1) {
                    currentPtr = currentPtr->left;
                }
                if(choice == 2) {
                    currentPtr = currentPtr->right;
                }
                continue;
            }

            // If user does not have a choice
            if(currentPtr->data.rightEventNumber == -1) {
                currentPtr = currentPtr->left;
                continue;
            }
            if(currentPtr->data.leftEventNumber == -1) {
                currentPtr = currentPtr->right;
                continue;
            }
        }
    }
};

#endif // GAMEDECISIONTREE_H