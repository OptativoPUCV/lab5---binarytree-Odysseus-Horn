#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    
  TreeMap *newTree = (TreeMap *) malloc(sizeof(TreeMap));
  newTree->root = NULL;
  newTree->current = NULL;
  
  newTree->lower_than = lower_than;
  
  return newTree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {

  
  TreeNode *new_node = createTreeNode(key, value); //nuevo nodo creado

  if(tree == NULL) return; //si el arbol no tiene nada retornamos

  tree->current = tree->root;

  if(tree->root == NULL) //si el arbol no tiene raiz, le asignamos el nuevo nodo como raiz.
  {
    tree->root = new_node;
    return;
  }
  
  while(1) 
  {
    if(is_equal(tree, key, tree->current->pair->key)) // si las claves son iguales no hacemos nada.
    {
      return;
    }

    if(tree->lower_than(key, tree->current->pair->key)) //si la clave es menor al current, lo llevamos al hijo izquierdo
    {
      tree->current = tree->current->left;
      if(tree->current == NULL) //si el nodo actual esta vacio, lo asignamos inmediatamente
      {
        tree->current = new_node;
        return;
      }
    }
    else
    {
      tree->current = tree->current->right;
      if(tree->current == NULL) //si el nodo actual esta vacio, lo asignamos inmediatamente
      {
        tree->current = new_node;
        return;
      }
    }
  }  
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {

  if(tree == NULL || tree->root == NULL) return NULL;
  
  tree->current = tree->root;

  while(tree->current != NULL)
  {
    if(is_equal(tree, key, tree->current->pair->key))
    {
      return tree->current->pair;
    }

    if(tree->lower_than(key, tree->current->pair->key))
    {
      tree->current = tree->current->left;
    }
    else
    {
      tree->current = tree->current->right;
    }
       
  }

  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
