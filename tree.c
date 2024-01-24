#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cart.h"
#include "retail_item.h"
#include "tree.h"


//search through linked list for a name, return # of times looped through
int llist_search_name(llnode* crt, char* name){
int count = 0;
//if llist is null return -1 for failure
if(crt == NULL) {
printf("Invalid cart node.\n");
return -1;
} else {
//else loop through linked list until find it or until end of list
while (crt->item->name != name && crt != NULL) {
count++;
crt = crt->next;
}
if (crt == NULL) {
//if couldn't find item return -1 for failure
printf("Item not found.\n");
return -1;
}else {
//item found and print count
 printf("LList search name count: %d \n", count);
 return count;
}
}
}//llist_search_name


//search through linked list for a number, return # of times looped through
int llist_search_number(llnode* crt, int numb){
int count = 0;
//if llist is null
if(crt == NULL) {
printf("Invalid cart node given.");
return -1;//empty list did not find number so return -1 for exit
}else{
//loop through 
while(crt->item->number != numb && crt != NULL) {
count++;
crt = crt->next;
}
if (crt == NULL) {
printf("Could not find item.");
return -1;
} else {
 printf("LList search number count: %d \n", count);
return count;
}
}
}//llist_search_number


//search through name tree for a name, return # of times looped through
int binary_search_name(Tree* tree, char* name) {
//if tree is null
if(tree == NULL) {
printf("Could not find item.\n");
return -1;
}
int countL = 0;
int countR = 0;
int comp = strcmp(name, tree->ll->name);

if (comp == 0) {
//If you found it do nothing so it exits
} else if (comp < 0) {
//if it less than look left
countL = binary_search_name(tree->left, name);
}
else if (comp > 0) {
//if its greater than look right
countR = binary_search_name(tree->right, name);
}
//return iteration num
return 1 + countR + countL;
}//binary_search_name


//search through number tree for a number, return # of times looped through
int binary_search_number(Tree* tree, int numb) {
//if tree is null
if(tree == NULL) {
return -1;
}
int countL = 0;
int countR = 0;
if (tree->ll->number == numb) {
//if found do nothing so it will exit with count
} else if(tree->ll->number < numb) {
//if greater than, go down right side of tree
countL = binary_search_number(tree->right, numb);
} else if (tree->ll->number > numb) {
//if less than, go down left side of tree
countR = binary_search_number(tree->left, numb);
}
//return iteration num
return 1 + countR + countL;
}//binary_search_number

//Build Tree
Tree* buildTree(llnode* crt, int p){
Tree* tree = NULL;
while (crt != NULL){//loop through tree and assign it values
tree = insert(tree, crt->item, p);
crt = crt->next;//move to next value
}
return tree;
}//buildTree


//Insert tree node into tree
Tree* insert(Tree* tree, retail_item* crt, int p) {
Tree* root = tree;
if (tree == NULL) {//tree is null create it
tree = (Tree*) malloc(sizeof(Tree));
tree->ll = crt;
tree->left = NULL;
tree->right = NULL;
return tree;
}else{
//loop through tree
while (tree != NULL) {
if (compare(tree, crt, p) == 0) {
//Dont insert if same
break;
}else if (compare(tree, crt, p) == 1 ) {
//look right
if (tree->right == NULL) {
Tree* node = (Tree*) malloc(sizeof(Tree));//insert
node->ll = crt;
node->right = NULL;
node->left = NULL;
tree->right = node;
break;
} else{
tree=tree->right;
//move to next
}
} else if (compare(tree, crt, p) == -1 ) {
//look left
if (tree->left == NULL) {
Tree* node = (Tree*) malloc(sizeof(Tree));//insert
node->ll = crt;
node->right = NULL;
node->left = NULL;
tree->left = node;
break;
} else{
tree=tree->left;
//move to next
}
}

}
}
return root;
}//insert


//Print Tree to test and see if functions worked
void printTree(Tree* tree) {
if (tree == NULL) {//if tree is empty do nothing
return;
}
//loop through tree and print values
printTree(tree->left);
printf("%d\n", tree->ll->number);
printTree(tree->right);
}//printTree


//Comparing value to tree value
int compare(Tree* tree, retail_item* crt, int p) {
//number
if (p == 0) {
if (tree->ll->number == crt->number) {
return 0;
} else if (tree->ll->number < crt->number) {
return 1;
} else if (tree->ll->number > crt->number) {
return -1;
}else{
return -5;
}

//name
}else if (p == 1) {
int cmp = strcmp(tree->ll->name, crt->name);
if (cmp == 0) {
return 0;
} else if (cmp < 0) {
return 1;
} else if (cmp > 0) {
return -1;
}else {
return -5;
}
}

//didnt work
return -5;
}//compare;


//Delete tree function
void deleteTree(Tree** tree, retail_item* item, int p) {
//Set values so tree isnt deleted
Tree* curr = *tree;
Tree* found = NULL;
Tree* parent = NULL;
if(curr == NULL) {
return;
}

parent = NULL;
while(curr != NULL) {
if (compare(curr, item, p) == 0) {
//if found item
found = curr;
break;
} else if(compare(curr, item, p) == -1) {
//if item is on left side of tree
parent = curr;
curr = curr->left;
}else {
//if item is on right side of tree
parent = curr;
curr = curr->right;
}
}

//if its not found in tree exit
if (found == NULL) {
return;
}


//CASE 1: Found is a leaf
//If no children
if (found->left == NULL && found->right == NULL) {
if (parent == NULL) {
free(found);
tree = NULL;
return;
}
//if parent is not NULL, so update child to be null
if (parent->left == found) {
parent->left = NULL;
} else if (parent->right == found) {
parent->right = NULL;
} else {
printf("Parent has invalid children\n");
return;
}
free(found);
return;
}

//CASE 2: Found is an interior node with one right child
//if no left child
if (found->left == NULL) {
if (parent->left  == found) {
parent->left = found->left;
} else if (parent->right == found) {
parent->right = found->left;
} else {
printf("Parent has invalid children\n");
}
free(found);
return;
}

//CASE 3: Found is an interior node with one left child
//If no right child
if(found->right == NULL) {
if (parent->left == found) {
parent->left = found->left;
} else if (parent->right == found) {
parent->right = found->left;
} else {
printf("Parent has invalid children\n");
return;
}
free(found);
return;
}


//CASE 4: Found is an interior node with two children

Tree* traverse = found->right;
Tree* traverseParent = traverse->left;

//Going left until reach a node with no left child
while (traverse->left != NULL) {
traverseParent = traverse;
traverse = traverse->left;
}

//Put data in found
found->ll = traverse->ll;

//check if traverse is a leaf node
if (traverse->left == NULL && traverse->right == NULL) {
//delete leaf node
if (traverseParent->left == traverse) {
traverseParent->left = NULL;
free(traverse);
}else if (traverseParent->right == traverse) {
traverseParent->right = NULL;
free(traverse);
} else {
printf("Parent of traversed node has invalid children\n");
return;
}
return;
}

//Traverse has a right subtree
if (traverse->left == NULL && traverse->right != NULL) {
if (traverseParent->left == traverse) {
traverseParent->left = traverse->right;
free(traverse);
} else if(traverseParent->right == traverse) {
traverseParent->right = traverse->right;
free(traverse);
}
}
return;

}//delete



//delete all function
void deleteAll(Tree** tree1, Tree** tree2, llnode** cart, int num) {
retail_item* ret = (retail_item*)malloc(sizeof(retail_item));
llnode* cart1 = *cart;
while(cart1 != NULL && cart1->item->number != num) {
cart1 = cart1->next;
}
if(cart1 == NULL) {
return;
}else {
ret = cart1->item;
}
deleteTree(tree1, ret, 0);
deleteTree(tree2, ret, 1);
*cart = delete_item(*cart, ret->number);
}//deleteAll


//Calculates runtimes of functions
void runTime(Tree* tree1, Tree* tree2, llnode* crt) {
//Counters 
int C1;
int C2;
int C3;
int C4;
int tot = 0;
//loop through each function to find run time (innacurate though because returns -1 if can't find item)
while(crt != NULL) {
C1 += binary_search_name(tree1, crt->item->name);
C2 += binary_search_number(tree2, crt->item->number);
C3 += llist_search_number(crt, crt->item->number);
C4 += llist_search_name(crt, crt->item->name);
tot++;
crt = crt->next;
}
//math to finalize time
C1 = C1/tot;
C2 = C2/tot;
C3 = C3/tot;
C4 = C4/tot;

printf("Binary search name time: %d , binary search number time: %d , llist find number time: %d llist find name time: %d \n", C1, C2, C3, C4);

}//runTime
