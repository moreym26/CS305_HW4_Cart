#ifndef TREE_H
#define TREE_H

#include "cart.h"
#include "retail_item.h"

//Tree struct
typedef struct tree Tree;
struct tree
{
	Tree *left;
	Tree *right;
	struct retail_item* ll;
};

//C Function Prototypes
int llist_search_name(llnode*, char* name);
int llist_search_number(llnode* crt, int num);
int binary_search_name(Tree*, char*);
int binary_search_number(Tree*, int);
Tree* buildTree(llnode*, int);
Tree* insert(Tree*, retail_item*, int);
void printTree(Tree*);
int compare(Tree*, retail_item*, int);
void printNumTab(int, int);
void printNameTab(int, char*);
void printR(int, Tree*, int);
void tree_print(Tree*, int);
void deleteTree(Tree**, retail_item*, int);
void deleteAll(Tree**, Tree**, llnode**, int num);
void runTime(Tree*, Tree*, llnode*);
#endif
