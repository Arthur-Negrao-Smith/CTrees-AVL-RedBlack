#ifndef RB_TREE_H
#define RB_TREE_H

typedef enum { RED , BLACK } RBcolor;
typedef enum { FALSE = 0, TRUE = 1 } Bool;

/** 
 *@brief Struct to represent the Red-Black node
 */
typedef struct RBnode {
    float data; ///< Node's data
    int RBcolor; ///< 0 for Black, 1 for Red
    struct RBnode *father; ///< Pointer to father node
    struct RBnode *left; ///< Pointer to left node
    struct RBnode *right; ///< Pointer to right node
} RBnode;


/*
 * @brief Struct to represent the Red-Black tree
 */
typedef struct {
    RBnode *root ; ///< Pointer to root node
    int length;    ///< Number of tree nodes
} RBtree; // raiz era pra ter cor em teoria e não coloquei ainda? não sei

extern RBnode *Nil;

RBtree *RB_create();
RBnode *RB_createnode(float data);

Bool RB_empty(RBtree *tree);
Bool RB_insert(RBtree *tree, float data);
Bool RB_delete(RBtree *tree, float data);

void RB_leftRotation( RBtree *tree, RBnode *node );
void RB_rightRotation( RBtree *tree, RBnode *node );

void RB_insertionFixup(RBtree *tree, RBnode *node);
void RB_deleteFixup(RBtree *tree, RBnode *node);

void RB_print(RBtree *tree);
#endif

