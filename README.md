README

A) Title and Author
Title: Binary Search Trees
Author: Sandra Ortellado

B) Purpose
The purpose of this program is to implement a binary search tree and store
integer keys and track how many times any given key has been inserted into 
the collection.

C) Help received
I used the trees parts 1 and 2 and binary search topics on Canvas.

D) Time spent
I spent 12 hours on this assignment.

E) Files included
* BinarySearchTree.cpp - Implementation of the Binary Search Tree class
* BinarySearchTree.h - Interface of the Binary Search Tree class
* Makefile - links and compiles files
* hw3.cpp - Main driver for testing the BinarySearchTree class

F) Instructions for compiling and running
Running make ; ./hw03 will run the program.

G) Testing strategy
I edited the given test file hw03.cpp to test the various edge cases of my
functions especially inserting and removing.

Questions:

1. It will use find_min() in the case that there is no left node to find the 
node who's value is closest to the parent node value, otherwise it will 
use find_max() of the left side of the tree for the same reason.

2. My find_min and find_max functions are not able to return a value
that does not point to a valid node because I have written in a check
that returns the original node if there is no left or right node
and the public functions do not allow for nullptr nodes to be passed
to the private function.

3. My function will return the original node called on, 5.

4. If left node doesn't exist, return original node, otherwise recurse on 
left side.

5. If right node doesn't exist, return original node, otherwise recurse on 
right side.

6. If node doesn't exist, return. If left and right nodes don't exist,
delete the node and return. If left node exists, recurse on left node.
If right node exists, recurse on right node. Else delete node.

