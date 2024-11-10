cmake_minimum_required(VERSION 3.24)
project(story_rpg)

set(CMAKE_CXX_STANDARD 23)

add_executable(story_rpg main.cpp Story.h Node.h GameDecisionTree.h)
