/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 using namespace std;


template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    Node * subroot = t -> right;
    Node * subrootl = subroot -> left;
    subroot -> left = t;
    t -> right = subrootl;
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
    t = subroot;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;

    //subroot->height = std::max(heightOrNeg1(subroot->left), heightOrNeg1(subroot->right))+1;
    //t = subroot;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
  Node * subroot = t -> left;
  Node * subrootl = subroot -> right;
  subroot -> right = t;
  t -> left = subrootl;
  functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
  // your code here
  t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
  t = subroot;
  t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
  //subroot->height = std::max(heightOrNeg1(subroot->left), heightOrNeg1(subroot->right))+1;
  //t = subroot;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}
//helper getbalance
template <class K, class V>
int AVLTree<K, V>::getbalance_(Node*& subtree)
{
  //if (subtree == NULL) return 0;
  return heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  if (subtree == NULL) {
    return;
  }
  if (subtree->left == NULL && subtree->right == NULL) {
    return;
  }
  int b = heightOrNeg1(subtree-> right) - heightOrNeg1(subtree -> left);
  if (b == 2) {
    int bb = heightOrNeg1(subtree -> right -> right) - heightOrNeg1(subtree -> right -> left);
    if (bb == -1) {
      rotateRightLeft(subtree);
    }
    if (bb == 1) {
      rotateLeft(subtree);
    }
  }

  if (b == -2) {
    int bb = heightOrNeg1(subtree -> left -> right) - heightOrNeg1(subtree -> left -> left);
    if (bb == -1) {
      rotateRight(subtree);
    }
    if (bb == 1) {
      rotateLeftRight(subtree);
    }
  }
  //subtree -> height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1;

    // your code here
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
  if (subtree == NULL) {
    subtree = new Node(key,value);
    return;
  }
  else if (key <  subtree -> key) {
    insert(subtree -> left, key, value);
  }
  else if (key > subtree -> key) {
    insert(subtree -> right, key,value);
  }
  subtree -> height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1;
  rebalance(subtree);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree -> left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree -> right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
            return;
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
          Node *tmp = subtree -> left;
          while(tmp -> right != NULL) {
            tmp = tmp -> right;
          }
          K tkey = tmp -> key;
          V tValue = tmp -> value;
          remove(subtree, tkey);
          subtree -> key = tkey;
          subtree -> value = tValue;

          //swap(subtree,tmp);
          //remove(subtree->left, key);
            /* two-child remove */
            // your code here

        } else {
          if (subtree -> left){
            Node *tmp = subtree;
            subtree = subtree -> left;
            delete tmp;
          } else {
            Node *tmp = subtree;
            subtree = subtree -> right;
            delete tmp;
          }
            /* one-child remove */
            // your code here
        }
        // your code here
    }
    subtree -> height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1;
    rebalance(subtree);

}
