#include "include/redblack.h"
#include <stdlib.h>

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
    node -> father = NULL;
    node -> left = NULL;
    node -> right = NULL;
    node -> RBcolor = RED; // new node inicialize being red

    return node;
}

Bool RB_empty(RBtree *tree) {
    // if the pointer is null
    if (!tree)
       return TRUE;
    // if the tree don't have a root
    if (!tree->root)
       return TRUE;     
    // It's not empty
    return FALSE;
}

RB_leftRotation( RBtree *tree, RBnode *father ) {
    RBnode *y = father->right; 
    father->right = y->left;

    if (y->left != Nil) {
      y->left->father = father;
    }
    y->father = father->father;
    if (father->father == Nil) {
        tree->root = y;
    }
    else if(father == father->father->left) {
        father->father->left = y;
    }
    else {
        father->father->left = y;
    }
    y->left = father;
    father->father = y;

    return 0;
}

RB_rightRotation(RBtree *tree, RBnode *father ) {
    RBnode *y = father->left;
    father->left = y->right;

    if (y->right != Nil) {
        y->right->father = father;
    }
    y->father = father->father;
    if (father->father == Nil) {
        tree = y;
    }
    else if(father==father->father->right) {
        father->father->right = y;
    }
    else {
        father->father->left = y;
    }
    y -> right = father;
    father->father = y;

    return 0;
}

RB_insertion(RBtree *tree, float data) {
    RBnode *node = RB_creatnode(data);
    RBnode *y = Nil;
    RBnode *x = tree->root;

    while(x != Nil) {
        y = x;
        if(node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->father = y;
    if(y == Nil) {
        tree->root = node;
    } else if(node->data < y->data) {
        y->left = node;       
    } else {
        y->right = node;
    }

    node->left = Nil;
    node->right = Nil;
    node -> RBcolor = RED;
}

RB_insertionFixup(RBtree *tree, RBnode *node) {
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

    return 0;
}
