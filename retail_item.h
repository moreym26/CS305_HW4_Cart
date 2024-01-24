#ifndef RETAIL_ITEM_H
#define RETAIL_ITEM_H

/* retail_item struct */
typedef struct retail_item {
  int number;
  char* name;
  int price_cents;
} retail_item;

/* function prototypes */
retail_item* create_retail_item (int, char*, int);
void print(retail_item*);

#endif
