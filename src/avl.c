#include "include/avl.h"
#include <stdlib.h>

AVLTree *AVL_create() {
  AVLTree *tree;
  tree = (AVLTree *)malloc(sizeof(AVLTree));

  // if an error occurs during memory allocation
  if (!tree)
    return NULL;

  tree->depth = 0;
  tree->length = 0;
  tree->root = NULL;

  return tree;
}

AVLNode *AVL_createNode(float data) {
  AVLNode *node;
  node = (AVLNode *)malloc(sizeof(AVLNode));

  // if an error occurs during memory allocation
  if (!node)
    return NULL;

  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return node;
}

Bool AVL_addLeftNode(AVLNode *father, AVLNode *child) {
  if (!father)
    return FALSE;

  father->left = child;
  return TRUE;
}

Bool AVL_addRightNode(AVLNode *father, AVLNode *child) {
  if (!father)
    return FALSE;

  father->right = child;
  return TRUE;
}

Bool AVL_isEmpty(AVLTree *tree) {
  // if the pointer is null
  if (!tree)
    return TRUE;

  // if the tree don't have a root
  if (!tree->root)
    return TRUE;

  // isn't empty
  return FALSE;
}
