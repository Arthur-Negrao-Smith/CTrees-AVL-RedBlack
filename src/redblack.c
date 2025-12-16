#include "include/redblack.h"
#include <stdlib.h>

REDBLACKtree *REBLACK_create() {
  REDBLACKtree *tree;
  tree = (REDBLACKtree*)malloc(sizeof(REDBLACKtree));

  // for any error that might occur during memory allocation
  if (!tree)
    return NULL;

  tree->root = NULL;
  tree->black_height = 0;
  tree->length = 0;

  return tree;
}

REDBLACKnode *REDBLACK_createnode(float data) {
    REDBLACKnode *node;
    node = (REDBLACKnode* )malloc(sizeof(REDBLACKnode));

    if (!node)
      return NULL;

    node -> data = data;
    node -> father = NULL;
    node -> left = NULL;
    node -> right = NULL;
    node -> REDBLACKcolor = RED; // new node inicialize being red

    return node;
}

Bool REDBLACK_empty(REDBLACKtree *tree) {
    // if the pointer is null
    if (!tree)
       return TRUE;
    // if the tree don't have a root
    if (!tree->root)
       return TRUE;     
    // It's not empty
    return FALSE;
}

REDBLACK_leftRotation( REDBLACKtree *tree, REDBLACKnode *father ) {
    REDBLACKnode *y = father->right; 
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

REDBLACK_rightRotation(REDBLACKtree *tree, REDBLACKnode *father ) {
    REDBLACKnode *y = father->left;
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

REDBLACK_insertion(REDBLACKtree *tree, float data) {
    REDBLACKnode *node = REDBLACK_creatnode(data);
    REDBLACKnode *y = Nil;
    REDBLACKnode *x = tree->root;

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
    node -> REDBLACKcolor = RED;
}

REDBLACK_insertionFixup(REDBLACKtree *tree, REDBLACKnode *node) {
    REDBLACKnode *uncle;
    while(node->father->REDBLACKcolor == RED) {
        if(node->father == node->father->father->left) { 
            uncle = node->father->father->right;
            if(uncle->REDBLACKcolor ==  RED) {
                node->father->REDBLACKcolor = BLACK;
                uncle->REDBLACKcolor = BLACK;
                node->father->father->REDBLACKcolor = RED;
                node = node->father->father;
            } else if (node == node->father->right) {
                node = node->father;
                REDBLACK_leftRotation(tree, node);
            }

            node->father->REDBLACKcolor = BLACK;
            node->father->father->REDBLACKcolor = RED;
            REDBLACK_rightRotation(tree, node->father->father);
        }
        else {
            uncle = node->father->father->left;
            if(node->REDBLACKcolor == RED) {
                node->father->REDBLACKcolor = BLACK;
                node->REDBLACKcolor = BLACK;
                node->father->father->REDBLACKcolor = RED;
                node = node->father->father;
            } else if(node == node->father->left) {
                node = node->father;
                REDBLACK_rightRotation(tree, node);
            }
            node->father->REDBLACKcolor = BLACK;
            node->father->father->REDBLACKcolor = RED;
            REDBLACK_leftRotation(tree, node->father->father);
        }
    }

    tree->root->REDBLACKcolor = BLACK;

    return 0;
}
