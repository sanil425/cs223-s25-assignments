#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

struct tree_node* helperCreateNode(const char* name) {
  struct tree_node* new_node = malloc(sizeof(struct tree_node));
  if (new_node == NULL) {
    printf("Error with memory allocation");
    exit(1);
  }
  strcpy(new_node->data.name, name); // Copy name into new node
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

struct tree_node* insert(const char* name, struct tree_node* root) {
  // Base case when root is NULL and we create new node
  if (root == NULL) {
    return helperCreateNode(name);
  }
  int compare = strcmp(name, root->data.name);
  if (compare < 0) {
    // name is less than roots name, so go left
    root->left = insert(name, root->left);
  }
  else if (compare > 0) {
    // name is more than roots name, so go right
    root->right = insert(name, root->right);
  }
  return root;
}

struct tree_node* find(const char* name, struct tree_node* root) {
  // Base case is when tree is empty or reached leaf with no match
  if (root == NULL) return NULL;

  // Compare name with current nodes name
  int compare = strcmp(name, root->data.name);
  // if names match
  if (compare == 0) {
    return root;
  }
  else if (compare < 0) {
    // go to left subtree as smaller
    return find(name, root->left);
  }
  else {
    // right subtree
    return find(name, root->right);
  }
}

void clear(struct tree_node* root) {
  if (root == NULL) {
    return; // tree is empty, functions job is done
  }
  // recursively clear left and right subtrees and then free current node
  clear(root->left);
  clear(root->right);
  free(root);
}

void helperPrint(struct tree_node* root, int depth, char childType) {
  // Base case
  if (root == NULL) return;

  // Draw tree
  // Indent base on depth
  for (int i = 0; i < depth; i++) {
    printf("   ");
  }
  // Print root or children with l or r labels
  if (depth == 0) printf("%s\n", root->data.name);  // print node
  else printf("%c:%s\n", childType, root->data.name);  // l: or r:

  // Recursivey call for left and right children chaning the level and child type
  helperPrint(root->left, depth + 1, 'l');
  helperPrint(root->right, depth + 1, 'r');
  
}

void print(struct tree_node* root) {
  helperPrint(root, 0, ' ');  // Start at depth 0 with no child label
}

void printSorted(struct tree_node* root) {
  if (root == NULL) {
    return;
  }
  printSorted(root->left);
  printf("%s\n", root->data.name);
  printSorted(root->right);
}

