#include "include/redblack.h"
#include <stdlib.h>

RBnode *Nil = NULL;

void RB_nodeNil() {
    Nil = (RBnode*)malloc(sizeof(RBnode));
    if (!Nil)
        return;
    
    
    Nil->RBcolor = BLACK;
    Nil->father = Nil;
    Nil->left = Nil;
    Nil->right = Nil;
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

    node -> RBcolor = RED; // new node inicialize being red
    node -> data = data;
    node -> father = Nil;
    node -> left = Nil;
    node -> right = Nil;

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
    if ( !tree )
        return FALSE;

    RBnode *node = RB_createnode(data);

    if (!node )
        return FALSE;

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
    RB_insertionFixup(tree, node);
    tree->length++;

    return TRUE;
}

void RB_insertionFixup(RBtree *tree, RBnode *node) {
    RBnode *uncle;
    while ( node->father->RBcolor == RED ) {

        if ( node->father == node->father->father->left ) { 
            uncle = node->father->father->right;

            if ( uncle->RBcolor ==  RED ) {
                node->father->RBcolor = BLACK;
                uncle->RBcolor = BLACK;
                node->father->father->RBcolor = RED;
                node = node->father->father;
            } else {      
                if ( node == node->father->right ) {
                    node = node->father;
                    RB_leftRotation(tree, node);
                }

            node->father->RBcolor = BLACK;
            node->father->father->RBcolor = RED;
            RB_rightRotation(tree, node->father->father);
            }   
        }
        else {
            uncle = node->father->father->left;
            
            if ( uncle->RBcolor == RED ) { //mudança na condicional de node para uncle
                node->father->RBcolor = BLACK;
                uncle->RBcolor = BLACK; //mudança aqui de node para uncle
                node->father->father->RBcolor = RED;
                node = node->father->father;
            } else {
                if ( node == node->father->left) {
                    node = node->father;
                    RB_rightRotation(tree, node);
                }
            node->father->RBcolor = BLACK;
            node->father->father->RBcolor = RED;
            RB_leftRotation(tree, node->father->father);
            }
        }
    }

    tree->root->RBcolor = BLACK;
}

RBnode *RB_search( RBtree *tree, float data ) {
    RBnode *current = tree->root;

    while ( current != Nil && data != current->data ) {
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return current; 
}

void RB_transplant( RBtree *tree, RBnode *removedNode, RBnode *replacementNode ) {
    if ( removedNode->father == Nil ) {
        tree->root = replacementNode;
    } else if (removedNode == removedNode->father->left) {
        removedNode->father->left = replacementNode;
    } else {
        removedNode->father->right = replacementNode;
    }
    replacementNode->father = removedNode->father;
}

RBnode *RB_minimumFixup( RBnode *node) {
    while ( node->left != Nil) {
        node = node->left;
    }
    return node;
}

Bool RB_delete( RBtree *tree, float data ) {
    RBnode *searchNode = RB_search(tree, data);
    if (searchNode == Nil) {
        return FALSE;
    }

    RBnode *deletedNode = searchNode;
    RBnode *replacementNode;
    RBcolor deletedColor = deletedNode->RBcolor;

    if ( searchNode->left == Nil ) {
        replacementNode = searchNode->right;
        RB_transplant(tree, searchNode, searchNode->right);
    } else if ( searchNode->right == Nil ) {
        replacementNode = searchNode->left;
        RB_transplant(tree, searchNode, searchNode->left);
    } else {
        deletedNode = RB_minimumFixup(searchNode->right);
        deletedColor = deletedNode->RBcolor;
        replacementNode = deletedNode->right;

        if ( deletedNode->father == searchNode ) {
            replacementNode->father = deletedNode;
        } else {
            RB_transplant(tree, deletedNode, deletedNode->right);
            deletedNode->right = searchNode->right;
            deletedNode->right->father = deletedNode;
        }

        RB_transplant(tree, searchNode, deletedNode);
        deletedNode->left = searchNode->left;
        deletedNode->right->father = deletedNode;
        deletedNode->RBcolor = searchNode->RBcolor;
    }

    if ( deletedColor == BLACK ) {
        RB_deleteFixup(tree, replacementNode);
    }

    free(searchNode);
    return TRUE;
}

void RB_deleteFixup( RBtree *tree, RBnode *node ) {
    RBnode *brother;
    while ( node != tree->root && node->RBcolor == BLACK ) {

        if ( node ==  node->father->left ) {
            brother = node->father->right;

            if ( brother->RBcolor == RED) {
                brother->RBcolor = BLACK;
                node->father->RBcolor = RED;
                RB_leftRotation(tree, node->father);
                brother = node->father->right;
            }

            if ( brother->left->RBcolor == BLACK && brother->right->RBcolor == BLACK) {
                brother->RBcolor = RED;
                node = node->father;
            } else {
                if ( brother->right->RBcolor == BLACK ) {
                    brother->left->RBcolor = BLACK;
                    brother->RBcolor = RED;
                    RB_rightRotation(tree, brother);
                    brother = node->father->right;
                }

                brother->RBcolor = node->father->RBcolor;
                node->father->RBcolor =  BLACK;
                brother->right->RBcolor = BLACK;
                RB_leftRotation(tree, node->father);
                node = tree->root;
            }
        } else {
            brother = node->father->left;

            if ( brother->RBcolor == RED) {
                brother->RBcolor = BLACK;
                node->father->RBcolor = RED;
                RB_rightRotation(tree, node->father);
                brother = node->father->left;
            }

            if ( brother->right->RBcolor == BLACK && brother->left->RBcolor == BLACK) {
                brother->RBcolor = RED;
                node = node->father;
            } else {
                if ( brother->left->RBcolor == BLACK ) {
                    brother->right->RBcolor = BLACK;
                    brother->RBcolor = RED;
                    RB_leftRotation(tree, brother);
                    brother = node->father->left;
                }

                brother->RBcolor = node->father->RBcolor;
                node->father->RBcolor = BLACK;
                brother->left->RBcolor = BLACK;
                RB_rightRotation(tree, node->father);
                node = tree->root;
                }
            }
    }
node->RBcolor = BLACK;
}

static void RB_printInOrder(RBnode *node) {
    if (node == Nil)
        return;

    RB_printInOrder(node->left);

    printf("%.2f(%c) ",
           node->data,
           node->RBcolor == RED ? 'R' : 'B');

    RB_printInOrder(node->right);
}

void RB_print(RBtree *tree) {
    if (!tree || tree->root == Nil)
        return;

    printf("[ ");
    RB_printInOrder(tree->root);
    printf("]");
}
