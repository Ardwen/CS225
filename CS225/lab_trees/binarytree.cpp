/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
using namespace std;
#include <vector>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param current
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* current) const
{
    // Base case
    if (current == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(current->left), height(current->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param current
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* current) const
{
    // Base case - null node
    if (current == NULL)
        return;

    // Print left subtree
    printLeftToRight(current->left);

    // Print this node
    std::cout << current->elem << ' ';

    // Print right subtree
    printLeftToRight(current->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* root) {
  if (root == NULL) {
    return;
  } else {
    Node* tmp;
    mirror(root->left);
    mirror(root->right);
    tmp = root->left;
    root->left = root->right;
    root->right = tmp;
  }
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{

    // your code here
    vector<T> path;
    path = inO(root, path);
    T tmp = path.front();
    for (typename vector<T>::iterator it = path.begin(); it != path.end(); it++) {
      if (tmp > (*it)) {
        return false;
      }
      tmp = (*it);
    }
    return true;
}

/**r
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursive(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* current) const
{

  if ((current -> left == NULL) && (current ->right == NULL)) {
    return true;
  }
  bool out = isOrderedRecursive(current->left) && isOrderedRecursive(current->right);
  if (!out) return false;

  if (current->left==NULL)
	{
		if (current->elem < max(current->right)) return true;
		else return false;
	}
	if (current->right==NULL)
	{
		if (current->elem > max(current->left)) return true;
		else return false;
	}
	if (current->elem > max(current->left) && current->elem < max(current->right))
	{
		return true;
	}
  else return false;
}


template <typename T>
int BinaryTree<T>::max(Node* current) const
{
	InorderTraversal<int> iot(current);
	int max = 0;
	for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
		if ((*it)->elem > max)
			max = (*it)->elem;
	}
	return max;
}

template <typename T>
vector<T> BinaryTree<T>::inO(BinaryTree::Node* current, std::vector<T>& treeVector) const{
    if(current == NULL){
      return treeVector;
    }
      treeVector = inO(current->left, treeVector);
      treeVector.push_back(current->elem);
      treeVector = inO(current->right, treeVector);
      return treeVector;
    }




/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
  vector<T> path;
  getPaths(root,path,paths);
  return;
    // your code here
}

template <typename T>
void BinaryTree<T>::getPaths(Node *cur, vector<T>path,vector<vector<T>>& paths) const
{
  if (cur == NULL) {
    return;
  }
  path.push_back(cur->elem);
  if (cur -> left == NULL && cur ->right == NULL) {
    paths.push_back(path);
    return;
    }
  getPaths(cur -> left, path,paths);
  getPaths(cur -> right, path,paths);
    // your code here
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return -1;
}
