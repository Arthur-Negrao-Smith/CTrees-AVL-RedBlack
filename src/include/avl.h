#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef enum { NORMAL_ORDER, REVERSE_ORDER } AVLOrder;
typedef enum { FALSE = 0, TRUE = 1 } Bool;

/**
 * @brief Struct to represent the AVL node
 */
typedef struct AVLNode {
  float data;            ///< Node's data
  int height;            ///< Node height
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
 *
 * @return A AVLTree if the memory allocation works, else returns NULL
 */
AVLTree *AVL_create();

/**
 * @Brief Create a AVL node
 *
 * @param data Information to add in node
 *
 * @return A AVLNode if the memory allocation works, else returns NULL
 */
AVLNode *AVL_createNode(float data);

/**
 * @Brief Check if the AVL is empty
 *
 * @param tree The tree to check
 *
 * @return Returns TRUE if the tree is empty or NULL, else returns FALSE
 */
Bool AVL_isEmpty(AVLTree *tree);

/**
 * @Brief Insert a float in the AVLTree
 *
 * @param tree The tree to insert a node
 * @param data The float to insert in tree
 *
 * @return Returns NULL if the tree is NULL or if a memory allocation failure
 * occurred, else returns a AVLNode pointer
 */
AVLNode *AVL_insert(AVLTree *tree, float data);

/**
 * @Brief Insert a node in AVLNode recursively
 *
 * @param node The root to insert a node
 * @param data The float to insert in tree
 *
 * @return Returns the inserted node pointer
 */
AVLNode *AVL_insertNode(AVLNode *node, float data);

Bool AVL_remove(AVLTree *tree, float data);
AVLNode *AVL_search(float data);

/**
 * @Brief Destroy the entire tree recursively
 *
 * @param tree The target tree to destroy
 */
void AVL_destroyTree(AVLTree *tree);

/**
 * @Brief Destroy a AVL node
 *
 * @param node The target node to destroy
 */
void AVL_destroyNode(AVLNode *node);

/**
 * @Brief Destroy the all nodes bellow (left and right) recursively
 *
 * @param node The first target node to destroy
 */
void AVL_destroyNodes(AVLNode *node);

/**
 * @Brief Get the max depth of the tree
 *
 * @param tree The tree to calculate the depth
 *
 * @return A number of levels (The root is depth 0)
 */
int AVL_getDepth(AVLTree *tree);

/**
 * @Brief Get height of a node
 *
 * @param node Target node to get your height
 *
 * @return A int with the current height
 */
int AVL_getHeight(AVLNode *node);

/**
 * @Brief Get the balance factor from a target node
 *
 * @param father The target node to receive a child
 * @param child The child node to add
 *
 * @return Returns the balance factor from the target node
 */
int AVL_getBalanceFactor(AVLNode *node);

/**
 * @Brief Add a child node on the left of target father node
 * * If the target node already have a left node, then the
 * * entire left subtree will be destroyed
 *
 * @param father The target node to receive a child
 * @param child The child node to add
 *
 * @return Returns FALSE if the father node is a NULL pointer, else returns TRUE
 */
Bool AVL_addLeftNode(AVLNode *father, AVLNode *child);

/**
 * @Brief Add a child node on the right of target father node
 * * If the target node already have a right node, then the
 * * entire left subtree will be destroyed
 *
 * @param tree The tree to destroy
 *
 * @return Returns FALSE if the father node is a NULL pointer, else returns TRUE
 */
Bool AVL_addRightNode(AVLNode *father, AVLNode *child);

/**
 * @Brief Do a left rotate in tree
 *
 * @param node Target to rotate
 *
 * @return Returns FALSE if the node is a NULL pointer or the right node is a
 * NULL pointer, else returns TRUE
 */
Bool AVL_leftRotate(AVLNode *node);

/**
 * @Brief Do a right rotate in tree
 *
 * @param node Target to rotate
 *
 * @return Returns FALSE if the node is a NULL pointer or the left node is a
 * NULL pointer, else returns TRUE
 */
Bool AVL_rightRotate(AVLNode *node);

/**
 * @Brief Do a double left rotate in tree
 *
 * @param node Target to rotate
 *
 * @return Returns FALSE if the node is a NULL pointer or the right node is a
 * NULL pointer, else returns TRUE
 */
Bool AVL_doubleLeftRotate(AVLNode *node);

/**
 * @Brief Do a double right rotate in tree
 *
 * @param node Target to rotate
 *
 * @return Returns FALSE if the node is a NULL pointer or the left node is a
 * NULL pointer, else returns TRUE
 */
Bool AVL_doubleRightRotate(AVLNode *node);

/**
 * @brief Print the entire avl tree in defined order
 *
 * @param tree The target tree to print
 * @param order The order to print
 */
void AVL_print(AVLTree *tree, AVLOrder order);

/*
 * @brief Print node recursively in ascending order
 *
 * @param node The target node to recursively print in ascending order
 */
void AVL_visitLeft(AVLNode *node);

/*
 * @brief Print node recursively in descending order
 *
 * @param node The target node to recursively print in descending order
 */
void AVL_visitRight(AVLNode *node);

#endif
