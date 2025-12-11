#include "include/avl.h"
#include <stdio.h>
#include <stdlib.h>

float max(float a, float b) {
  if (a > b)
    return a;

  return b;
}

AVLTree *AVL_create() {
  AVLTree *tree;
  tree = (AVLTree *)malloc(sizeof(AVLTree));

  // if an error occurs during memory allocation
  if (!tree)
    return NULL;

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
  node->height = 0;
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

int AVL_getHeight(AVLNode *node) {
  if (!node)
    return 0;

  return node->height;
}

int AVL_getBalanceFactor(AVLNode *node) {
  if (!node)
    return 0;

  return AVL_getHeight(node->left) - AVL_getHeight(node->right);
}

int AVL_getDepth(AVLTree *tree) {
  if (!tree)
    return 0;

  if (!tree->root)
    return 0;

  return max(AVL_getHeight(tree->root->left), AVL_getHeight(tree->root->right));
}

AVLNode *AVL_insert(float data, AVLTree *tree) {
  if (!tree)
    return NULL;

  AVLNode *node = AVL_createNode(data);

  if (!node)
    return NULL;

  if (!tree->root) {
    tree->root = node;
    tree->length = 1;
    return node;
  }

  // TODO: Finalize the function
  return NULL;
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

void AVL_visitLeft(AVLNode *node) {
  // stop condition
  if (!node)
    return;

  AVL_visitLeft(node->left);

  printf("%f ", node->data);

  AVL_visitLeft(node->right);
}

void AVL_visitRight(AVLNode *node) {
  // stop condition
  if (!node)
    return;

  AVL_visitRight(node->right);

  printf("%f ", node->data);

  AVL_visitRight(node->left);
}

void AVL_print(AVLTree *tree, AVLOrder order) {
  if (!tree)
    return;

  printf("[ ");

  if (order == NORMAL_ORDER) {
    AVL_visitLeft(tree->root);

  } else if (order == REVERSE_ORDER) {
    AVL_visitRight(tree->root);
  }

  printf("]");
  return;
}
