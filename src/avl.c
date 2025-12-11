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

void AVL_destroyTree(AVLTree *tree) {
  if (!tree)
    return;

  // destroy all tree's nodes recursively
  AVL_destroyNodes(tree->root);
}

void AVL_destroyNodes(AVLNode *node) {
  // stop condition
  if (!node)
    return;

  // cleanup all left nodes recursively
  AVL_destroyNodes(node->left);

  // cleanup all right nodes recursively
  AVL_destroyNodes(node->right);

  // cleanup the current node
  free(node);
}

void AVL_destroyNode(AVLNode *node) {
  if (!node)
    return;

  free(node);
}

Bool AVL_addLeftNode(AVLNode *father, AVLNode *child) {
  if (!father)
    return FALSE;

  // to avoid wild pointer
  if (father->left)
    AVL_destroyNodes(father->left);

  father->left = child;

  return TRUE;
}

Bool AVL_addRightNode(AVLNode *father, AVLNode *child) {
  if (!father)
    return FALSE;

  // to avoid wild pointer
  if (father->right)
    AVL_destroyNodes(father->right);

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

Bool AVL_leftRotate(AVLNode *node) {
  if (!node)
    return FALSE;

  AVLNode *right_child = node->right;
  if (!right_child)
    return FALSE;

  AVLNode *left_of_right_child = right_child->left;

  // realize the rotate
  AVL_addLeftNode(right_child, node);
  AVL_addRightNode(node, left_of_right_child);

  // updating the hight
  node->height = max(AVL_getHeight(node->left), AVL_getHeight(node->right)) + 1;
  right_child->height =
      max(AVL_getHeight(right_child->left), AVL_getHeight(right_child->right)) +
      1;

  return TRUE;
}

Bool AVL_rightRotate(AVLNode *node) {
  if (!node)
    return FALSE;

  AVLNode *left_child = node->left;
  if (!left_child)
    return FALSE;

  AVLNode *right_of_left_child = left_child->right;

  // realize the rotate
  AVL_addRightNode(left_child, node);
  AVL_addLeftNode(node, right_of_left_child);

  // updating the hight
  node->height = max(AVL_getHeight(node->left), AVL_getHeight(node->right)) + 1;
  left_child->height =
      max(AVL_getHeight(left_child->left), AVL_getHeight(left_child->right)) +
      1;

  return TRUE;
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
