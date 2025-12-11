#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef enum { NORMAL_ORDER, REVERSE_ORDER } AVLOrder;
typedef enum { FALSE = 0, TRUE = 1 } Bool;

/**
 * @brief Struct to represent the AVL node
 */
typedef struct AVLNode {
  float data;            ///< Node's data
  int height;            ///< Node hight
  struct AVLNode *left;  ///< Pointer to left node
  struct AVLNode *right; ///< Pointer to right node
} AVLNode;

/**
 * @brief Struct to represent the AVL tree
 */
typedef struct {
  AVLNode *root; ///< Pointer to root node
  int length;    ///< Number of tree nodes
} AVLTree;

/**
 * @Brief Get the max value
 *
 * @param a First value to compare
 * @param b Second value to compare
 *
 * @return The largest number
 */
float max(float a, float b);

/**
 * @Brief Create a AVL tree
 */
AVLTree *AVL_create();

/**
 * @Brief Create a AVL node
 *
 * @param data Information to add in node
 *
 * @return The current node with the data
 */
AVLNode *AVL_createNode(float data);

/**
 * @Brief Check if the AVL is empty
 *
 * @param tree The tree to check
 *
 * @return Return TRUE if the tree is empty or NULL, else return FALSE
 */
Bool AVL_isEmpty(AVLTree *tree);
AVLNode *AVL_insert(float data, AVLTree *tree);
Bool AVL_remove(float data, AVLTree *tree);
AVLNode *AVL_search(float data);
void AVL_destroyTree(AVLTree *tree);
void AVL_destroyNode(AVLNode *node);
void AVL_destroyNodes(AVLNode *node);

int AVL_getDepth(AVLTree *tree);
int AVL_getHeight(AVLNode *node);
int AVL_getBalanceFactor(AVLNode *node);

Bool AVL_addLeftNode(AVLNode *father, AVLNode *child);
Bool AVL_addRightNode(AVLNode *father, AVLNode *child);

int AVL_leftRotate(AVLNode *child, AVLNode *father, AVLNode *grandfather,
                   AVLTree *tree);
int AVL_rightRotate(AVLNode *child, AVLNode *father, AVLNode *grandfather,
                    AVLTree *tree);
int AVL_doubleLeftRotate(AVLNode *child, AVLNode *father, AVLNode *grandfather,
                         AVLTree *tree);
int AVL_doubleRightRotate(AVLNode *child, AVLNode *father, AVLNode *grandfather,
                          AVLTree *tree);

void AVL_print(AVLTree *tree, AVLOrder order);
void AVL_visitLeft(AVLNode *node);
void AVL_visitRight(AVLNode *node);

#endif
