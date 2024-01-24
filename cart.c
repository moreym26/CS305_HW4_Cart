/********************************************************
 * HW 4: starter code for search tree assignments.
 * Fall 2023
 * filename: cart.c
 * models a shopping cart of retail_items as a collection
 * supports adding a new retail_item and printing
 * the cart, including the total cost
 * 
 * compile with retail_item.c and main.c
 * see makefile
 ******************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include "retail_item.h"
#include "cart.h"

/* functions on receipt structs */

/******************************************************
 * create_cart
 * returns NULL (an empty linked list)
 *****************************************************
 */
llnode* create_cart() {
  return NULL;
}

/*****************************************************
 * add_item
 * parameter: cart ** cart_ptr
 * parameter: retail_item item
 *
 * recurisively adds item to the end of the cart llist 
 * unless it is already in the list then it exits
 ****************************************************
 */
llnode* add_item(llnode* crt, retail_item* it) {
  if(crt == NULL) {
    llnode* tmp = (llnode *) malloc(sizeof(llnode));
    tmp->item = it;
    tmp->next = NULL;
    return tmp;
  }else if (crt->item->number == it->number){ //if item exits, just exit
    perror("Add item: Failed, cannot add duplicate item to list\n");
    free(it->name);
    free(it);
    return crt;
  }else{ //put node at the end of list as it was not found
    crt->next = add_item(crt->next, it);
  }
  return crt;
}

/***********************************************************
 * delete_item
 * parameter: llnode* cart_ptr
 * parameter: int item_num
 *
 * if the item with matching item_num is found in the cart,
 * it is recursively deletes 
 * if nothing is deleted ruturns
 * note: only deletes first item with matching item_num in list
 ***********************************************************
 */
llnode* delete_item(llnode* cart_ptr, int item_num){
  if(cart_ptr==NULL)
    return NULL;
  else if (cart_ptr->item->number == item_num){ //item found 
    llnode* tmp = cart_ptr->next;
    free(cart_ptr->item->name);  //free the heap name
    free(cart_ptr->item);        //free the item object
    free(cart_ptr);      
    return tmp;
  }else{                         //keep looking
    cart_ptr->next = delete_item(cart_ptr->next, item_num);
  }
  return cart_ptr;
}
    
/***************************************************************
 * print_cart
 * parameter: cart *crt
 * prints the current retail items and total price of the cart
 ***************************************************************
 */
void print_cart(llnode* crt) {
  printf("Cart:\n");
  int total = 0;
  while(crt != NULL) {
    total = total + crt->item->price_cents;
    print(crt->item);
    crt = crt->next;
  }

  int total_dollars = (int) total / 100;
  int total_cents = total - 100*total_dollars;
  printf("Total: $%d.%02d\n", total_dollars, total_cents);
  printf("\n");
  return;
}

/************************************************************
 * free_cart
 * parameter: cart *crt
 *
 * frees the memory for the cart recursively
 ************************************************************
 */
void free_cart(llnode* crt) {
  if(crt == NULL) {
    return;
  }
  free_cart(crt->next);
  free(crt->item->name);  //free the heap name
  free(crt->item);        //free the item object
  free(crt);              //free the llist node
}
