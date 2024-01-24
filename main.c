/****************************************************
 * HW 4: starter code for search tree assignments.
 * Fall 2023
 *
 * compile with cart.c and retail_item.c
 * see makefile
 * compile: make
 * cli usage: ./run <input file with items>
 * the input file has <int: number> <string: name> <int:price>
 ****************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include "cart.h"
#include "retail_item.h"
#include "tree.h"
/* prototypes */
int run_test(char* );

/****************************************************************
 * main 
 * using void paramater since we are not using command line 
 * arguments for this program
 ****************************************************************
 */
int main(int argc, char* argv[]) {
  if (argc != 2){
    perror("Usage: ./run <input file with items>. Exiting");
    exit(EXIT_FAILURE);
  }
  run_test(argv[1]);
}

/*************************************************************** 
 * run_test
 * runs a test, creating carts and adding/deleting items
 ***************************************************************
 */
int run_test(char* fn) {
  /* create two carts */
  /* note: using pointers for carts so the cart data can be 
     modified */
  FILE* fp = fopen(fn, "r");
  if(fp==NULL){
    perror("Cannot open input file");
    exit(EXIT_FAILURE);
  }
  llnode* fred = create_cart();

  /* create retail items */
  /* note: not using pointers to retail_items since once they are created
   * they are not later modified -- only used as data */
  int rc, number, price;
  char* name;
  while(fscanf(fp, " %d %ms %d \n",&number, &name ,&price) != EOF){
    printf("Adding: %d %s %d\n", number, name, price);
    fred=add_item(fred, create_retail_item(number, name, price));
  }
  fclose(fp);

  /* print the cart */
  print_cart(fred);

  /* delete item */
  printf("Trying to delete item 1234\n"); 
  fred = delete_item(fred, 1234);
  print_cart(fred);

  /* delete item */
  printf("Trying to delete item 10000\n");
  fred = delete_item(fred, 10000);
  print_cart(fred);

  /* delete items */
  printf("Trying to delete item 3222\n");
  fred = delete_item(fred, 3222);
  printf("Trying to delete item 3033\n");
  fred = delete_item(fred, 3033);
  printf("Trying to delete item 2121\n");
  fred = delete_item(fred, 2121);
  printf("Trying to delete item 1234\n");
  fred = delete_item(fred, 1234);
  print_cart(fred);

  //----------------------my tests----------------------
  Tree* george = NULL;
  george = buildTree(fred, 0);
  printf("Original Name Tree:\n");
  printTree(george);
  
  //create retail items and add it to george and fred
  retail_item* food = create_retail_item(7007, "Oreos", 2319);
  retail_item* RI = create_retail_item(1888, "Froot Loops", 1773);
  printf("Adding Item 7007 and 1888 to number tree.\n");
  insert(george, food, 0);
  insert(george, RI, 0);
  fred = add_item(fred, RI);
  fred = add_item(fred, food);
  
  //print before and after tree in order to see it insert and delete
  printf("After insert: \n");
  print_cart(fred);
  printTree(george);
  Tree** tree = &george;
  printf("Deleting Item 1888\n");
  deleteTree(tree, RI, 0);
  printf("After delete: \n");
  printTree(george);
  print_cart(fred);
  printf("End of number test :) \n");


  //Make another tree
  printf("\n");
  printf("\n");
  Tree* orange = NULL;
  orange = buildTree(fred, 1);
  printf("Original Tree:\n");
  printTree(orange);
  
  
  //add retail items to orange and fred
  printf("Adding Nutella Cookies and Purple Converse to name tree.\n");
  retail_item* ret = create_retail_item(2023, "Nutella Cookies", 2000000);
  insert(orange, ret, 1);
  retail_item* newIt = create_retail_item(8345, "Purple Converse", 9274);
  insert(orange, newIt, 1);
  fred = add_item(fred, newIt);
  fred = add_item(fred, ret);
  
  
  //print before and after tree in order to see it insert and delete
  printf("After Insert:\n");
  printTree(orange);
  printf("Deleting Nutella Cookies from name tree \n");
  Tree** banana = &orange;
  deleteTree(banana, ret, 1);
  printf("After Delete:\n");
  printTree(orange);
  printf("End of name test :) \n");
  printf("\n");
  printf("\n");


  //Search tests
  int BSName = binary_search_name(orange, "Snickers");
  int BSNumber = binary_search_number(george, 1121);
  int LSNumber = llist_search_number(fred, 2023);
  int LSName = llist_search_name(fred, "Froot Loops");
  printf("Binary search name count: %d \n", BSName);
  printf("Binary search number count: %d \n", BSNumber);
  printf("Test 3 :)\n");
  print_cart(fred);
 

  //Search Times Tests
  runTime(orange, george, fred);

  
  /* free memory for cart */
  free(george);
  free(orange);
  //free_cart(fred);
  

  return EXIT_SUCCESS;
} /* end run_test */
