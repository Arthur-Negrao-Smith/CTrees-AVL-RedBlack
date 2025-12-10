#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef enum { NORMAL_ORDER, REVERSE_ORDER } AVLOrder;
typedef enum { FALSE = 0, TRUE = 1 } Bool;

/**
 * @brief Struct to represent the AVL node
 */
typedef struct AVLNode {
  float data;            ///< Node's data
  struct AVLNode *left;  ///< Pointer to left node
  struct AVLNode *right; ///< Pointer to right node
} AVLNode;

/**
 * @brief Struct to represent the AVL tree
 */
typedef struct {
  AVLNode *root; ///< Pointer to root node
  int depth;     ///< Max tree depth
  int length;    ///< Number of tree nodes
} AVLTree;

AVLTree *AVL_create();
AVLNode *AVL_createNode(float data);

Bool AVL_isEmpty(AVLTree *tree);
Bool AVL_insert(float data, AVLTree *tree);
Bool AVL_remove(float data, AVLTree *tree);

Bool AVL_addLeftNode(AVLNode *father, AVLNode *child);
Bool AVL_addRightNode(AVLNode *father, AVLNode *child);

int AVL_leftRotation(AVLNode *child, AVLNode *father, AVLNode *grandfather,
                     AVLTree *tree);
int AVL_rightRotation(AVLNode *child, AVLNode *father, AVLNode *grandfather,
                      AVLTree *tree);
int AVL_doubleLeftRotation(AVLNode *child, AVLNode *father,
                           AVLNode *grandfather, AVLTree *tree);
int AVL_doubleRightRotation(AVLNode *child, AVLNode *father,
                            AVLNode *grandfather, AVLTree *tree);

void AVL_print(AVLTree *tree, AVLOrder order);
void AVL_visitLeft(AVLNode *node);
void AVL_visitRight(AVLNode *node);

#endif
