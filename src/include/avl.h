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
  int frequency;         ///< Frequency at which the node repeats
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
 * @brief Get the max value
 *
 * @param a First value to compare
 * @param b Second value to compare
 *
 * @return The largest number
 */
float max(float a, float b);

/**
 * @brief Create a AVL tree
 *
 * @return A AVLTree if the memory allocation works. Otherwise, returns NULL
 */
AVLTree *AVL_create();

/**
 * @brief Create a AVL node
 *
 * @param data Information to add in node
 *
 * @return A AVLNode if the memory allocation works. Otherwise, returns NULL
 */
AVLNode *AVL_createNode(float data);

/**
 * @brief Check if the AVL is empty
 *
 * @param tree The tree to check
 *
 * @return Returns TRUE if the tree is empty or NULL. Otherwise, returns FALSE
 */
Bool AVL_isEmpty(AVLTree *tree);

/**
 * @brief Update the height of a target node
 *
 * @param node Target node to update
 */
void AVL_updateHeight(AVLNode *node);

/**
 * @brief If necessary balance the local tree
 *
 * @param node Node to balance
 *
 * @return If node is NULL or the node don't have childs, then returns NULL.
 * Otherwise, returns new locally root
 */
AVLNode *AVL_balanceLocally(AVLNode *node);

/**
 * @brief Insert a float in the AVLTree
 *
 * @param tree The tree to insert a node
 * @param data The float to insert in tree
 *
 * @return Returns NULL if the tree is NULL or if a memory allocation failure
 * occurred. Otherwise, returns a new tree root pointer
 */
AVLNode *AVL_insert(AVLTree *tree, float data);

/**
 * @brief Insert a node in AVLNode recursively
 *
 * @param node The root to insert a node
 * @param data The float to insert in the tree
 *
 * @return If node is NULL, then returns NULL. Otherwise, returns the new local
 * root
 */
AVLNode *AVL_insertNode(AVLNode *node, float data);

/**
 * @brief Remove a tree node
 *
 * @param tree Tree to remove a node
 * @param data Data of the node to remove
 *
 * @return If the tree is NULL or empty or the the tree don't has this value,
 * then returns NULL. Otherwise, returns the new root tree
 */
AVLNode *AVL_remove(AVLTree *tree, float data);

/**
 * @brief Remove a node of the a subtree
 *
 * @param node Current root to search the node
 * @param data Data of the node to remove
 *
 * @return If the node is NULL or empty or the subtree don't has this value,
 * then returns NULL. Otherwise, returns the new local root
 */
AVLNode *AVL_removeNode(AVLNode *node, float data);

/**
 * @brief Find the min value tree node
 *
 * @param node Root node of the subtree
 *
 * @return If node is NULL, then returns NULL. Otherwise, returns the min node
 * of the subtree.
 */
AVLNode *AVL_findMinNode(AVLNode *node);

/**
 * @brief Search a data inner the a AVLTree
 *
 * @param tree Tree to search
 * @param data Target data to find
 *
 * @return Returns NULL if tree are NULL. Returns NULL if the tree are void.
 * Returns NULL if the data aren't in the Tree. Else, returns a AVLNode with
 * the target data
 */
AVLNode *AVL_search(AVLTree *tree, float data);

/**
 * @brief Search a data inner the a AVLNode's subtree recursively
 *
 * @param node Node to search inner of node's subtrees
 * @param data Target data to find
 *
 * @return Returns NULL if the data aren't in the Tree, else returns a AVLNode
 * with the target data
 */
AVLNode *AVL_searchNode(AVLNode *node, float data);

/**
 * @brief Destroy the entire tree recursively
 *
 * @param tree The target tree to destroy
 */
void AVL_destroyTree(AVLTree *tree);

/**
 * @brief Destroy a AVL node
 *
 * @param node The target node to destroy
 */
void AVL_destroyNode(AVLNode *node);

/**
 * @brief Destroy the all nodes bellow (left and right) recursively
 *
 * @param node The first target node to destroy
 */
void AVL_destroyNodes(AVLNode *node);

/**
 * @brief Get the max depth of the tree
 *
 * @param tree The tree to calculate the depth
 *
 * @return A number of levels (The root is depth 0)
 */
int AVL_getDepth(AVLTree *tree);

/**
 * @brief Get height of a node
 *
 * @param node Target node to get your height
 *
 * @return A int with the current height
 */
int AVL_getHeight(AVLNode *node);

/**
 * @brief Get the balance factor from a target node
 *
 * @param node Node to get your balance
 *
 * @return Returns the balance factor from the target node
 */
int AVL_getBalanceFactor(AVLNode *node);

/**
 * @brief Add a child node on the left of the target parent node
 * * If the target node already has a left node, then the
 * * entire left subtree will be freed
 *
 * @param parent The target node to receive a child
 * @param child The child node to add
 * @param destructive When TRUE, the existing left subtree of the parent
 * node is freed before assigning the new child
 *
 * @return Returns FALSE if the parent node is a NULL pointer. Otherwise,
 * returns TRUE
 */
Bool AVL_addLeftNode(AVLNode *parent, AVLNode *child, Bool destructive);

/**
 * @brief Add a child node on the right of the target parent node
 * * If the target node already has a right node, then the
 * * entire left subtree will be freed
 *
 * @param parent The target node to receive a child
 * @param child The child node to add
 * @param destructive When TRUE, the existing right subtree of the parent
 * node is freed before assigning the new child
 *
 * @return Returns FALSE if the parent node is a NULL pointer. Otherwise,
 * returns TRUE
 */
Bool AVL_addRightNode(AVLNode *parent, AVLNode *child, Bool destructive);

/**
 * @brief Do a left rotate in tree
 *
 * @param node Target to rotate
 *
 * @return Returns FALSE if the node is a NULL pointer or the right node is a
 * NULL pointer, else returns TRUE
 *
 * @return Returns NULL if the node is a NULL pointer or the left node is a
 * NULL pointer, else returns the right child node (new local root)
 */
AVLNode *AVL_leftRotate(AVLNode *node);

/**
 * @brief Do a right rotate in tree
 *
 * @param node Target to rotate
 *
 * @return Returns NULL if the node is a NULL pointer or the left node is a
 * NULL pointer, else returns the left child node (new local root)
 */
AVLNode *AVL_rightRotate(AVLNode *node);

/**
 * @brief Do a double left rotate in tree
 *
 * @param node Target to rotate
 *
 * @return Returns NULL if the node is a NULL pointer or the left node is a
 * NULL pointer, else returns the left child of right node (new local root)
 */
AVLNode *AVL_doubleLeftRotate(AVLNode *node);

/**
 * @brief Do a double right rotate in tree
 *
 * @param node Target to rotate
 *
 * @return Returns NULL if the node is a NULL pointer or the left node is a
 * NULL pointer, else returns the right child of the left node (new local
 * root)
 */
AVLNode *AVL_doubleRightRotate(AVLNode *node);

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
