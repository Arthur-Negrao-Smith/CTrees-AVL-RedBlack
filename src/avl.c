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

Bool AVL_addLeftNode(AVLNode *father, AVLNode *child, Bool destructive) {
  if (!father)
    return FALSE;

  // to avoid memory leaks
  if (father->left && destructive)
    AVL_destroyNodes(father->left);

  father->left = child;

  return TRUE;
}

Bool AVL_addRightNode(AVLNode *father, AVLNode *child, Bool destructive) {
  if (!father)
    return FALSE;

  // to avoid memory leaks
  if (father->right && destructive)
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

AVLNode *AVL_leftRotate(AVLNode *node) {
  if (!node)
    return NULL;

  AVLNode *right_child = node->right;
  if (!right_child)
    return NULL;

  AVLNode *left_of_right_child = right_child->left;

  // realize the rotate
  AVL_addLeftNode(right_child, node, FALSE);
  AVL_addRightNode(node, left_of_right_child, FALSE);

  // updating the height
  node->height = max(AVL_getHeight(node->left), AVL_getHeight(node->right)) + 1;
  right_child->height =
      max(AVL_getHeight(right_child->left), AVL_getHeight(right_child->right)) +
      1;

  return right_child;
}

AVLNode *AVL_rightRotate(AVLNode *node) {
  if (!node)
    return NULL;

  AVLNode *left_child = node->left;
  if (!left_child)
    return NULL;

  AVLNode *right_of_left_child = left_child->right;

  // realize the rotate
  AVL_addRightNode(left_child, node, FALSE);
  AVL_addLeftNode(node, right_of_left_child, FALSE);

  // updating the height
  node->height = max(AVL_getHeight(node->left), AVL_getHeight(node->right)) + 1;
  left_child->height =
      max(AVL_getHeight(left_child->left), AVL_getHeight(left_child->right)) +
      1;

  return left_child;
}

AVLNode *AVL_doubleLeftRotate(AVLNode *node) {
  if (!node)
    return NULL;

  if (!node->right)
    return NULL;

  // do the double rotation
  node = AVL_rightRotate(node);
  node = AVL_leftRotate(node);

  return node;
}

AVLNode *AVL_doubleRightRotate(AVLNode *node) {
  if (!node)
    return NULL;

  if (!node->left)
    return NULL;

  // do the double rotation
  node = AVL_leftRotate(node);
  node = AVL_rightRotate(node);

  return node;
}

AVLNode *AVL_insertNode(AVLNode *node, float data) {

  // stop condition
  if (!node)
    return AVL_createNode(data);

  // TODO: Implement frequency
  // positioning the new node
  if (data <= node->data)
    node->left = AVL_insertNode(node->left, data);
  else
    node->right = AVL_insertNode(node->right, data);

  // updating the new node height
  node->height = max(AVL_getHeight(node->left), AVL_getHeight(node->right)) + 1;

  int current_balance = AVL_getBalanceFactor(node);

  // double left case
  if (current_balance < -1 && data < node->right->data) {
    AVL_doubleLeftRotate(node);
    return node->right;
  }

  // double right case
  if (current_balance > 1 && data > node->left->data) {
    AVL_doubleRightRotate(node);
    return node->left;
  }

  // left case
  if (current_balance < -1 && data > node->right->data) {
    AVL_leftRotate(node);
    return node->right;
  }

  // right case
  if (current_balance > 1 && data < node->left->data) {
    AVL_doubleRightRotate(node);
    return node->left;
  }

  // if the node is already balanced
  return node;
}

AVLNode *AVL_insert(AVLTree *tree, float data) {
  if (!tree)
    return NULL;

  AVLNode *node = AVL_createNode(data);

  if (!node)
    return NULL;

  // if is the first node
  if (!tree->root) {
    tree->root = node;
    tree->length = 1;
    return node;
  }

  // cleanup unused node
  AVL_destroyNode(node);

  node = AVL_insertNode(tree->root, data);

  // if all occurs ok
  if (node) {
    tree->length++;

    // update tree root, because it may have been rotated
    tree->root = node;
  }

  return node;
}

AVLNode *findMinNode(AVLNode *node) {
  // invalid argument (node) passed
  if (!node)
    return NULL;

  // if the current node is the min value
  if (!node->left)
    return node;

  // call recursively until don't have a left node
  return AVL_findMinNode(node->left);
}

AVLNode *AVL_removeNode(AVLNode *node, float data) {
  // stop condition: the tree don't have this data
  if (!node)
    return NULL;

  AVLNode *removed_node;
  // if the data is less than data of the current node
  if (data < node->data) {
    removed_node = AVL_removeNode(node->left, data);

    // if the data is greater than data of the current node
  } else if (data > node->data) {
    removed_node = AVL_removeNode(node->right, data);

    // else the current node is the correct
  } else {

    AVLNode *aux_node;
    // have two childrens
    if (node->left && node->right) {
      aux_node = AVL_findMinNode(node->right);

      node->data = aux_node->data;

      // remove the min node
      node->right = AVL_removeNode(node->right, aux_node->data);

      // don't have childrens
    } else if (!node->left && !node->right)

      removed_node = node;
  }

  return removed_node;
}

AVLNode *AVL_remove(AVLTree *tree, float data) {
  if (!tree)
    return NULL;

  if (!tree->root)
    return NULL;

  AVLNode *node = AVL_removeNode(tree->root, data);

  // if don't finded
  if (!node)
    return NULL;

  // TODO: Finalize the Remove and update the tree root

  // removed node
  return node;
}

AVLNode *AVL_searchNode(AVLNode *node, float data) {
  // stop condition: if the tree don't have the data
  if (!node)
    return NULL;

  // if the data is greater than the data of the current node
  if (data < node->data)
    return AVL_searchNode(node->left, data);

  // if the data is less than the data of the current node
  if (data > node->data)
    return AVL_searchNode(node->right, data);

  // if the node have the searched data
  return node;
}

AVLNode *AVL_search(AVLTree *tree, float data) {
  // if the tree is NULL
  if (!tree)
    return NULL;

  // if the tree is void
  if (!tree->root)
    return NULL;

  return AVL_searchNode(tree->root, data);
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
