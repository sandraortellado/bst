/*
 * BinarySearchTree.cpp
 * COMP15
 * Spring 2020
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure
 */

#include <cstring>
#include <iostream>
#include <limits>

#include "BinarySearchTree.h"

using namespace std;

BinarySearchTree::BinarySearchTree()
{
        root = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        if (root) {
                post_order_delete(root);
                root = nullptr;
        }
          // not really necessary, since the tree is going
                         // away, but might want to guard against someone
                         // using a pointer after deleting
}

/* post_order_delete
 * Purpose: Recursively deletes all Nodes in the tree in a post-order fashion.
 * Parameters: node pointer
 * Returns: nothing
 */
void BinarySearchTree::post_order_delete(Node *node)
{
        // TODO: students write code here
        // (hint: use a post-order traversal to remove all nodes)
        if (!node) {
                return;
        }
        if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return;
        }
        if (node->left) {
                post_order_delete(node->left);
        }
        if (node->right) {
                post_order_delete(node->right);
        }
        delete node;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
        if (source.root) {
                root = pre_order_copy(source.root);
        } else {
                root = nullptr;
        }
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source)
{
        // TODO: Students write code here
        // check for self-assignment
        if (source.root == root) {
                return *this;
        }

        if (source.root) {
                // delete current tree if it exists
                post_order_delete(root);
                // use pre-order traversal to copy the tree
                root = pre_order_copy(source.root);
        } else {
                root = nullptr;
        }

        // don't forget to "return *this"
        return *this;
}

/* pre_order_copy
 * Purpose: Recursively copies all Nodes in the tree in a pre-order fashion
 * Parameters: node pointer
 * Returns: Node pointer
 */
BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const
{
        // TODO: Students write code here
        // (hint: use a pre-order traversal to copy details from the
        // node to a new node)
        Node *copyNode = new Node;
        copyNode->data = node->data;
        copyNode->count = node->count;
        if (node->left == nullptr && node->right == nullptr) {
                copyNode->left = nullptr;
                copyNode->right = nullptr;
                return copyNode;
        } 
        if (node->left == nullptr) {
                copyNode->left = nullptr;
        }
        if (node->right == nullptr) {
                copyNode->right = nullptr;
        }
        if (node->left) {
                copyNode->left = pre_order_copy(node->left);
        }
        if (node->right) {
                copyNode->right = pre_order_copy(node->right);
        }
        return copyNode;
        
}

int BinarySearchTree::find_min() const
{
        if (root == nullptr)
                return numeric_limits<int>::max(); // INT_MAX

        return find_min(root)->data;
}

/* find_min
 * Purpose: Returns the address of the Node with the smallest data value.
 * Parameters: node pointer
 * Returns: address of the Node with the smallest data value
 */
BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const
{
        if (node->left == nullptr) {
                return node;
        } 
        return find_min(node->left);
}

int BinarySearchTree::find_max() const
{
        if (root == nullptr)
                return numeric_limits<int>::min(); // INT_MIN

        return find_max(root)->data;
}

/* find_max
 * Purpose: Returns the address of the Node with the largest data value
 * Parameters: node pointer
 * Returns: address of the Node with the largest data value
 */
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const
{
        if (node->right == nullptr) {
                return node;
        } 
        return find_max(node->right);
}

bool BinarySearchTree::contains(int value) const
{
        if (root == nullptr) {
                return false;
        }
        return contains(root, value);
}

/* contains
 * Purpose: Return true if the tree contains the given value
 * Parameters: node pointer, value integer
 * Returns: boolean
 */
bool BinarySearchTree::contains(Node *node, int value) const
{
        if (node->data == value) {
                return true;
        }
        if (node->data > value) {
                if (node->left == nullptr) {
                        return false;
                }
                return contains(node->left, value);
        }
        if (node->data < value) {
                if (node->right == nullptr) {
                        return false;
                }
                return contains(node->right, value);
        }
        return false;
}


void BinarySearchTree::insert(int value)
{
        if (!root) {
                Node *newnode = new Node;
                newnode->data = value;
                newnode->count = 1;
                newnode->left = nullptr;
                newnode->right = nullptr;
                root = newnode;  
        } else {
                insert(root, value);
        }
}

/* insert
 * Purpose: inserts node with given value into tree
 * Parameters: node pointer, value integer
 * Returns: nothing
 */
void BinarySearchTree::insert(Node *node, int value)
{
        if (!node) {
                Node *newnode = new Node;
                newnode->data = value;
                newnode->count = 1;
                newnode->left = nullptr;
                newnode->right = nullptr;
                root = newnode;
        }
        if (node->data == value) {
                node->count += 1;
        }
        if (node->right && node->data < value) {
                insert(node->right, value);
        }
        if (node->left && node->data > value) {
                insert(node->left, value);
        }
        if (!node->right && node->data < value) {
                Node *newnode = new Node;
                newnode->data = value;
                newnode->count = 1;
                newnode->left = nullptr;
                newnode->right = nullptr;
                node->right = newnode;
        }
        if (!node->left && node->data > value) {
                Node *newnode = new Node;
                newnode->data = value;
                newnode->count = 1;
                newnode->left = nullptr;
                newnode->right = nullptr;
                node->left = newnode;
        }
}

bool BinarySearchTree::remove(int value)
{
        if (!root || !contains(value)) {
                return false;
        } else if (!root->right && !root->left) {
                if (root->data == value) {
                        delete root;
                        root = nullptr;
                        return true;
                } 
                return false;
        }
        if (value > root->data) {
                return remove(root->right, root, value);
        }
        if (value < root->data) {
                return remove(root->left, root, value);
        }
         if (root->data == value && root->left) {
                int max = find_max(root->left)->data;
                bool temp = remove(root->left, root, max);
                root->data = max;
                return temp;

        }
        if (root->data == value && root->right) {
                int min = find_min(root->right)->data;
                bool temp = remove(root->right, root, min);
                root->data = min;
                return temp;
        }
        return false;
        // return remove(root, &root, value);
}

// TODO:  Students uncomment one of the following remove functions
//        and implement it.  You only have to do one, though if you
//        want to explore both, that's ok, but turn in the program
//        with one of them working!
//
/* remove
 * Purpose: removes node with given value into tree
 * Parameters: node pointer for node and parent node, value integer
 * Returns: boolean
 */
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
        // TODO: Students write code here
        // (cannot be a lazy removal)

        if (node->data == value && !node->right && !node->left) {
                delete node;
                if (parent->data > value) {
                        parent->left = nullptr;
                }
                if (parent->data < value) {
                        parent->right = nullptr;
                }
                return true;
        }
        if (node->data == value && node->left) {
                int max = find_max(node->left)->data;
                bool temp = remove(node->left, node, max);
                node->data = max;
                return temp;

        }
        if (node->data == value && node->right) {
                int min = find_min(node->right)->data;
                bool temp = remove(node->right, node, min);
                node->data = min;
                return temp;
        }
        if (node->data != value) {
                if (node->data > value && node->left) {
                        return remove(node->left, node, value);
                }
                if (node->data < value && node->right) {
                        return remove(node->right, node, value);
                }
                return false;
        }
        return false;


}

// bool BinarySearchTree::remove(Node *node, Node **ptr_to_ptr_to_me, int value)
// {
//         // TODO:  Students write code here
// }


int BinarySearchTree::tree_height() const
{
        if (!root) {
                return -1;
        }
        return tree_height(root);
}

/* tree_height
 * Purpose: calculates height of tree
 * Parameters: node pointer
 * Returns: integer height
 */
int BinarySearchTree::tree_height(Node *node) const
{
        int left = 0;
        int right = 0;
        if (!node) {
                return -1;
        }
        if (node->left == nullptr && node->right == nullptr) {
                return 0;
        }
        if (node->left) {
                left = tree_height(node->left);
        }
        if (node->right) {
                right = tree_height(node->right);
        }
        return 1 + max(left, right);
}


int BinarySearchTree::node_count() const
{
        return node_count(root);
}

/* node_count
 * Purpose: returns the total number of nodes
 * Parameters: node pointer
 * Returns: count integer
 */
int BinarySearchTree::node_count(Node *node) const
{
        // if (node->left == nullptr && node->right == nullptr) {
        //         return 1;
        // }
        if (!node) {
                return 0;
        }
        return 1 + node_count(node->left) + node_count(node->right);

}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

/* count_total
 * Purpose: return the sum of all the node values (including duplicates)
 * Parameters: node pointer
 * Returns: sum integer
 */
int BinarySearchTree::count_total(Node *node) const
{
        if (!node) {
                return 0;
        }
        return node->count * node->data + count_total(node->left) + count_total(node->right);
}

BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
                                                      Node *child) const
{
        if (node == nullptr)
                return nullptr;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        size_t      numLayers  = tree_height() + 1;
        size_t      levelWidth = 4;
        const char *rootPrefix = "-> ";

        // Need numLayers * levelWidth characters for each layer of tree.
        // Add an extra levelWidth characters at front to avoid if statement
        // 1 extra char for nul character at end
        char *start = new char[(numLayers + 1) * levelWidth + 1];

        print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
        delete[] start;
}

// Logic and Output Reference: 
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
                                  const char *const fullLine,
                                  const char *const branch) const
{
        if (node == nullptr)
                return;

        // 4 characters + 1 for nul terminator
        using TreeLevel                    = char[5];
        static const int       levelLength = sizeof(TreeLevel) - 1;
        static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
                               CONNECT = "   |";
        // Copies prev into dest and advances dest by strlen(prev)
        auto set = [](char *dest, const char *prev) {
                size_t p = strlen(prev);
                return (char *)memcpy(dest, prev, p) + p;
        };


        print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

        // Clear any characters that would immediate precede the "branch"
        // Don't need to check for root (i.e start of array),fullLine is padded
        set(currPos - levelLength, EMPTY);

        // Terminate fullLine at current level
        *currPos = '\0';

        std::cerr << fullLine << branch << node->data
                  << (node->count > 1 ? "*" : "") << endl;

        // Connect upper branch to parent
        if (branch == UP)
                set(currPos - levelLength, CONNECT);

        // Connect lower branch to parent
        print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}
