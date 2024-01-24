#ifndef CART_H
#define CART_H

#include "retail_item.h"

/* cart struct, defined as a linked list
   each node has retail_item data and a pointer to the next cart item
*/
typedef struct llnode_tag llnode;
struct llnode_tag {
  retail_item* item;   // item stored in the node
  llnode* next;        // next cart node in linked list
};

/* function prototypes */
llnode* create_cart();
llnode* add_item(llnode*, retail_item*);
llnode* delete_item(llnode*, int);
void print_cart(llnode*);
void free_cart(llnode*);

#endif
