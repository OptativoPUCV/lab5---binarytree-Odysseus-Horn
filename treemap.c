#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode {
  Pair *pair;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
};

struct TreeMap {
  TreeNode *root;
  TreeNode *current;
  int (*lower_than)(void *key1, void *key2);
};

int is_equal(TreeMap *tree, void *key1, void *key2) {
  if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
    return 1;
  else
    return 0;
}

TreeNode *createTreeNode(void *key, void *value) {
  TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
  if (new == NULL)
    return NULL;
  new->pair = (Pair *)malloc(sizeof(Pair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  return new;
}

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2)) {

  TreeMap *newTree = (TreeMap *)malloc(sizeof(TreeMap));
  newTree->root = NULL;
  newTree->current = NULL;

  newTree->lower_than = lower_than;

  return newTree;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {

  if (tree == NULL)
    return; // si el arbol no tiene nada retornamos

  if (searchTreeMap(tree, key) !=
      NULL) // si las claves son iguales no hacemos nada.
  {
    return;
  }

  if (tree->root ==
      NULL) // si el arbol no tiene raiz, le asignamos el nuevo nodo como raiz.
  {
    tree->root = createTreeNode(key, value); // nuevo nodo creado;
    tree->current = tree->root;
    return;
  }

  tree->current = tree->root;

  while (1) {
    if (tree->lower_than(key, tree->current->pair->key)) {
      if (tree->current->left == NULL) {
        tree->current->left = createTreeNode(key, value); // nuevo nodo creado;
        tree->current->left->parent = tree->current;
        tree->current = tree->current->left;
        return;
      }
      tree->current = tree->current->left;
    } else {
      if (tree->current->right == NULL) {
        tree->current->right = createTreeNode(key, value);
        tree->current->right->parent = tree->current;
        tree->current = tree->current->right;
        return;
      }
      tree->current = tree->current->right;
    }
  }
}

TreeNode *minimum(TreeNode *x) {

  if (x->left == NULL) {
    return x;
  }
  return minimum(x->left);
}

void removeNode(TreeMap *tree, TreeNode *node) {
  if (tree == NULL)
    return;

  // ambos hijos del nodo son NULL
  if (node->left == NULL && node->right == NULL) {
    if (node->parent == NULL) {
      tree->root = NULL;
      return;
    }

    if (node->parent->left == node) {
      node->parent->left = NULL;
    } else {
      node->parent->right = NULL;
    }
  } // caso de que hayan dos hijos
  else if (node->left != NULL && node->right != NULL) {

    TreeNode *minNode = minimum(node->right);

    node->pair = minNode->pair;

    removeNode(tree, minNode);

  } else if (node->left != NULL) // en caso de que solo tenga un hijo izquierdo
  {
    if (node->parent == NULL) {
      tree->root = node->left;
      return;
    }

    node->left->parent = node->parent;

    if (node == node->parent->left)
      node->parent->left = node->left;
    else
      node->parent->right = node->left;

  } else {
    if (node->parent == NULL) {
      tree->root = node->right;
      return;
    }

    if (node == node->parent->right)
      node->parent->right = node->right;
    else
      node->parent->left = node->right;

    node->right->parent = node->parent;
  }
}

void eraseTreeMap(TreeMap *tree, void *key) {
  if (tree == NULL || tree->root == NULL)
    return;

  if (searchTreeMap(tree, key) == NULL)
    return;
  TreeNode *node = tree->current;
  removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key) {

  if (tree == NULL || tree->root == NULL)
    return NULL;

  tree->current = tree->root;

  while (tree->current != NULL) {
    if (is_equal(tree, key, tree->current->pair->key)) {
      return tree->current->pair;
    }

    if (tree->lower_than(key, tree->current->pair->key)) {
      tree->current = tree->current->left;
    } else {
      tree->current = tree->current->right;
    }
  }

  return NULL;
}

Pair *upperBound(TreeMap *tree, void *key) 
{  
  if(searchTreeMap(tree, key) != NULL)
  {
    return tree->current->pair;
  }
  
  tree->current = tree->root;
  TreeNode *aux_node = tree->current;
  while(tree->current != NULL)
  {  
    if(tree->lower_than(key, tree->current->pair->key))
      aux_node = tree->current;
    
    if(tree->lower_than(key, tree->current->pair->key))
    {
      tree->current = tree->current->left;
    }
    else
    {
      tree->current = tree->current->right;
    }
  }  

  if(tree->lower_than(aux_node->pair->key, key))
    return NULL;
  
  return aux_node->pair;
}

Pair *firstTreeMap(TreeMap *tree) {
  if (tree == NULL)
    return NULL;

  tree->current = minimum(tree->root);

  return tree->current->pair;
}

Pair *nextTreeMap(TreeMap *tree) { // 8123

  if (tree->current->right != NULL) 
  {
    tree->current = minimum(tree->current->right);
    return tree->current->pair;
  } 
  else 
  {
    TreeNode *index_node = tree->current->parent;
    while (index_node != NULL) {
      if (tree->lower_than(tree->current->pair->key, index_node->pair->key)) 
      {  
        tree->current = index_node;
        return index_node->pair;
      }
        index_node = index_node->parent;
    }
    return NULL;
  } 
}
