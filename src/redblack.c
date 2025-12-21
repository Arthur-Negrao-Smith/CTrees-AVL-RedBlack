#include "include/redblack.h"
#include <stdlib.h>

RBnode *Nil = NULL;

void RB_nodeNil() {
    Nil = (RBnode*)malloc(sizeof(RBnode));
    if (!Nil)
        return;
    
    
    Nil->father = NULL;
    Nil->left = NULL;
    Nil->right = NULL;
    Nil->RBcolor = BLACK;
}


RBtree *RB_create() {
  RBtree *tree;
  tree = (RBtree*)malloc(sizeof(RBtree));

  // for any error that might occur during memory allocation
  if (!tree)
    return NULL;

  tree->root = Nil;
  tree->length = 0;

  return tree;
}

RBnode *RB_createnode(float data) {
    RBnode *node;
    node = (RBnode* )malloc(sizeof(RBnode));

    if (!node)
      return NULL;

    node -> data = data;
    node -> father = Nil;
    node -> left = Nil;
    node -> right = Nil;
    node -> RBcolor = RED; // new node inicialize being red

    return node;
}

Bool RB_empty(RBtree *tree) {
    // if the pointer is null
    if (!tree)
       return TRUE;
    // if the tree don't have a root
    if (tree->root == Nil)
       return TRUE;     
    // It's not empty
    return FALSE;
}

void RB_leftRotation( RBtree *tree, RBnode *node ) {
    RBnode *rightChild = node->right; 
    node->right = rightChild->left;

    if (rightChild->left != Nil) {
      rightChild->left->father = node;
    }
    rightChild->father = node->father;
    if (node->father == Nil) {
        rightChild->father = Nil;
        tree->root = rightChild;
    }
    else if(node == node->father->left) {
        node->father->left = rightChild;
    }
    else {
        node->father->right = rightChild;
    }
    rightChild->left = node;
    node->father = rightChild;

}

void RB_rightRotation(RBtree *tree, RBnode *node ) {
    RBnode *leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != Nil) {
        leftChild->right->father = node;
    }
    leftChild->father = node->father;
    if (node->father == Nil) {
        leftChild->father = Nil;
        tree->root = leftChild;
    }
    else if(node == node->father->right) {
        node->father->right = leftChild;
    }
    else {
        node->father->left = leftChild;
    }
    leftChild -> right = node;
    node->father = leftChild;

}

Bool RB_insert(RBtree *tree, float data) {
    RBnode *node = RB_createnode(data);
    RBnode *parent = Nil;
    RBnode *current = tree->root;

    while(current != Nil) {
        parent = current;
        if(node->data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->father = parent;
    if(parent == Nil) {
        tree->root = node;
    } else if(node->data < parent->data) {
        parent->left = node;       
    } else {
        parent->right = node;
    }

}

void RB_insertionFixup(RBtree *tree, RBnode *node) {
    RBnode *uncle;
    while(node->father->RBcolor == RED) {
        if(node->father == node->father->father->left) { 
            uncle = node->father->father->right;
            if(uncle->RBcolor ==  RED) {
                node->father->RBcolor = BLACK;
                uncle->RBcolor = BLACK;
                node->father->father->RBcolor = RED;
                node = node->father->father;
            } else if (node == node->father->right) {
                node = node->father;
                RB_leftRotation(tree, node);
            }

            node->father->RBcolor = BLACK;
            node->father->father->RBcolor = RED;
            RB_rightRotation(tree, node->father->father);
        }
        else {
            uncle = node->father->father->left;
            if(node->RBcolor == RED) {
                node->father->RBcolor = BLACK;
                node->RBcolor = BLACK;
                node->father->father->RBcolor = RED;
                node = node->father->father;
            } else if(node == node->father->left) {
                node = node->father;
                RB_rightRotation(tree, node);
            }
            node->father->RBcolor = BLACK;
            node->father->father->RBcolor = RED;
            RB_leftRotation(tree, node->father->father);
        }
    }

    tree->root->RBcolor = BLACK;

}
