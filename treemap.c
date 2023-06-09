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
    TreeMap* new = (TreeMap*) malloc(sizeof(TreeMap));
    if (new == NULL) return NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap* tree, void* key, void* value){
    if (tree == NULL) return; 
    if (tree->root == NULL) { 
        tree->root = createTreeNode(key, value);
        tree->current = tree->root;
        return;
    }
    TreeNode* current = tree->root;
    while (current != NULL) {
        if (is_equal(tree, key, current->pair->key)) return; 
        if (tree->lower_than(key, current->pair->key)) { 
            if (current->left == NULL) { 
                current->left = createTreeNode(key, value);
                current->left->parent = current;
                tree->current = current->left;
                return;
            } else {
                current = current->left; 
            }
        } else { 
            if (current->right == NULL) { 
                current->right = createTreeNode(key, value);
                current->right->parent = current;
                tree->current = current->right;
                return;
            } else {
                current = current->right; 
            }
        }
    }
}


TreeNode * minimum(TreeNode * x) {
    if (x == NULL) return NULL;
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

void removeNode(TreeMap * tree, TreeNode* node) {
    if (node == NULL) return;

    if (node->left == NULL && node->right == NULL) {  
        if (node == tree->root) {
            free(node->pair);
            free(node);
            tree->root = NULL;
        } else {
            if (node->parent->left == node) node->parent->left = NULL;
            else node->parent->right = NULL;
            free(node->pair);
            free(node);
        }
    } else if (node->left == NULL || node->right == NULL) {  
        TreeNode* child = node->left == NULL ? node->right : node->left;
        if (node == tree->root) {
            free(node->pair);
            free(node);
            tree->root = child;
            child->parent = NULL;
        } else {
            child->parent = node->parent;
            if (node->parent->left == node) node->parent->left = child;
            else node->parent->right = child;
            free(node->pair);
            free(node);
        }
    } else { 
        TreeNode* minNode = minimum(node->right);
        Pair* temp = node->pair;
        node->pair = minNode->pair;
        minNode->pair = temp;
        removeNode(tree, minNode);
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair* searchTreeMap(TreeMap* tree, void* key) {
    TreeNode* current = tree->root;
    while (current != NULL) {
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else if (tree->lower_than(current->pair->key, key)) {
            current = current->right;
        } else {
            
            tree->current = current;
            return current->pair;
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
