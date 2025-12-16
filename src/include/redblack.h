#ifndef REDBLACK_TREE_H
#define REDBLACK_TREE_H

typedef enum { RED , BLACK } REDBLACKcolor;
typedef enum { FALSE = 0, TRUE = 1 } Bool;

/** 
 *@brief Struct to represent the Red-Black node
 */
typedef struct REDBLACKnode {
    float data; ///< Node's data
    int REDBLACKcolor; ///< 0 for Black, 1 for Red
    struct REDBLACKnode *father; ///< Pointer to father node
    struct REDBLACKnode *left; ///< Pointer to left node
    struct REDBLACKnode *right; ///< Pointer to right node
} REDBLACKnode;


/*
 * @brief Struct to represent the Red-Black tree
 */
typedef struct {
    REDBLACKnode *root ; ///< Pointer to root node
    int length;    ///< Number of tree nodes
    int black_height; ///< Number of the black height for balancing
} REDBLACKtree; // raiz era pra ter cor em teoria e não coloquei ainda? não sei

extern REDBLACKtree *Nil;

REDBLACKtree *REDBLACK_create();
REDBLACKnode *REDBLACK_createnode(float data);

Bool REDBLACK_empty(REDBLACKtree *tree);
Bool REDBLACK_insert(REDBLACKtree *tree, float data);
Bool REDBLACK_delete(REDBLACKtree *tree, float data);

Bool REDBLACK_addLeftNode(REDBLACKnode *father, REDBLACKnode *child);
Bool REDBLACK_addRightNode(REDBLACKnode *father, REDBLACKnode *child);

int REDBLACK_leftRotation( REDBLACKtree *tree, REDBLACKnode *father );
int REDBLACK_rightRotation( REDBLACKtree *tree, REDBLACKnode *father );

int REDBLACK_doubleLeftRotation( REDBLACKtree *tree, REDBLACKnode *father );
int REDBLACK_doubleRightRotation( REDBLACKtree *tree, REDBLACKnode *father );

void REDBLACK_print(REDBLACKtree *tree);

#endif

