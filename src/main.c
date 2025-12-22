#include "include/avl.h"
#include "include/redblack.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

  AVLTree *tree = AVL_create();
  printf("Creating the tree...\n");
  if (!tree) {
    printf("Erro to create the tree\n");
    return 1;
  }

  float numbers_to_add[] = {1.0, 2.0, 2.5, 3.3, 5.0, 5.0, 1.2};
  for (int i = 0; i < (sizeof(numbers_to_add) / sizeof(numbers_to_add[0]));
       i++) {
    printf("Adding number %f in AVL tree...\n", numbers_to_add[i]);
    AVL_insert(tree, numbers_to_add[i]);
  }

  printf("\nPrinting the tree: ");
  AVL_print(tree, NORMAL_ORDER);

  printf("\nPrinting the tree in reverse order: ");
  AVL_print(tree, REVERSE_ORDER);

  printf("\n\nSearching the number %f...\n", numbers_to_add[2]);
  AVLNode *tmp_node = AVL_search(tree, numbers_to_add[2]);
  if (tmp_node)
    printf("The result is: %f\n", tmp_node->data);
  else
    printf("Failed to search for node...\n");

  printf("\nThe current tree root is %f and the length of the tree is %d\n",
         tree->root->data, tree->length);

  printf("\nRemoving the %f number...\n", numbers_to_add[1]);
  tmp_node = AVL_remove(tree, numbers_to_add[1]);

  if (tmp_node)
    printf("The node removed is %f and the length of the root is: %d\n",
           numbers_to_add[1], tree->length);
  else
    printf("Failed to remove a node...\n");

  printf("\nRemoving the %f number...\n", numbers_to_add[4]);
  tmp_node = AVL_remove(tree, numbers_to_add[4]);

  if (tmp_node)
    printf("The node removed is %f and the length of the root is: %d\n",
           numbers_to_add[4], tree->length);
  else
    printf("Failed to remove a node...\n");

  printf("Print all the tree: ");
  AVL_print(tree, NORMAL_ORDER);

  printf("\n\nDestroying the tree...\n");
  AVL_destroyTree(tree);
  // Red-Black Tree
  printf("\n\n--- Now Testing Red Black Tree ---\n\n");
  printf("Warning: The Red Black Tree use the predecessor when deleting a node with two children\n\n");
  RB_nodeNil();
  RBtree *rbtree = RB_create();
  printf("Creating the Tree...\n");
  if (!rbtree) {
      printf("Error to create the Tree\n");
      return 1;
  }

  for (int i = 0; i < (sizeof(numbers_to_add) / sizeof(numbers_to_add[0])); i++) {
      printf("Adding number %f in Red Black Tree...\n", numbers_to_add[i]);
      RB_insert(rbtree, numbers_to_add[i]);
  }

  printf("\nPrinting the Red Black Tree: ");
  RB_print(rbtree);
  printf("\n");

  printf("Searching the number %f...\n", numbers_to_add[2]);
  RBnode *aux_node = RB_search(rbtree, numbers_to_add[2]);
  if (aux_node != Nil)
      printf("The result is: %f\n", aux_node->data);
  else 
      printf("Failed to search for node...\n");

  printf("\nThe current Tree root is %f\n",
          rbtree->root->data);
  
  // Checking the black length of the tree
  int blackLength = RB_treeLength(rbtree);

  if (blackLength == -1) {
      printf("Red Black Tree is not valid(Length is diferent in each subtree)\n");
  } else {
      printf("The black length of the Tree is = %d\n", blackLength);
  }

  printf("\nRemoving the %f number...\n", numbers_to_add[1]);
  Bool removed = RB_delete(rbtree, numbers_to_add[1]);

  if (removed) {
    blackLength = RB_treeLength(rbtree);
    printf("The node removed is %f and the length of the tree is: %d\n",
              numbers_to_add[1], blackLength);
  } else 
    printf("Failed to remove a node...\n");
  
  printf("\nPrint all the Red Black Tree: ");
  RB_print(rbtree);
  printf("\n");

  printf("\nThe current Tree root is %f\n",
          rbtree->root->data);
  
  // Checking the black length of the tree
  blackLength = RB_treeLength(rbtree);

  if (blackLength == -1) {
      printf("Red Black Tree is not valid(Length is diferent in each subtree)\n");
  } else {
      printf("The black length of the Tree is = %d\n", blackLength);
  }

  printf("\nDestroying the Tree...\n");
  RB_destroy(rbtree);

  return 0;
}
