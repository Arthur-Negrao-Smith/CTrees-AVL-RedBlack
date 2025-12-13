#include "include/avl.h"
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

  printf("\n\nSearching the third number...\n");
  AVLNode *tmp_node = AVL_search(tree, numbers_to_add[3]);
  if (tmp_node)
    printf("The result is: %f\n", tmp_node->data);
  else
    printf("Failed to search for node...\n");

  printf("\nThe current tree root is: %f", tree->root->data);

  printf("\n\nDestroying the tree...\n");
  AVL_destroyTree(tree);

  return 0;
}
