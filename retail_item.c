/************************************************************
 * HW 4: starter code for search tree assignments.
 * Fall 2023
 * 
 * filename: retail_item.c
 * models a retail_item as an number, name, and price
 * supports creation of retail_item and printing
 * 
 * must compile with cart.c and main.c
 * see makefile
 ************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cart.h"
#include "retail_item.h"

/* functions on retail_item structs */

/************************************************************* 
 *  create_retail_item
 * parameters: int num, char *name, int price
 *
 * sets the values of retail item according to the parameters
 * and returns the structure
 *************************************************************
 */
retail_item* create_retail_item (int num, char *name, int price) {
  retail_item* ret = (retail_item*) malloc(sizeof(struct retail_item));
  if(num < 0) {
    num = 0;
  }
  if(price < 0) {
    price = 0;
  }
  ret->number = num;         // set number
  ret->price_cents = price;  // set price
  ret->name = name;  // copy the item name from stack to heap
  return ret;
}

/*************************************************************** 
 * print
 * parameter: retail_item ri
 *
 * prints the retail item number, name, and price separated by tabs
 ***************************************************************
 */
void print(retail_item* ri) {
  printf("Item %d\t%s\t$%d.%02d\n", ri->number, ri->name, ri->price_cents / 100, ri->price_cents - ri->price_cents);
  return;
}
