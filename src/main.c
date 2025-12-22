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



  return 0;
}
