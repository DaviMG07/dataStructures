#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int value;
    int height;
    struct Node* left;
    struct Node* right;
} node;

node* newNode(int);
node* insert(node*, int);
node* delete(node*, int);
node* search(node*, int);
node* leftRotation(node*);
node* rightRotation(node*);
node* leftRightRotation(node*);
node* rightLeftRotation(node*);
node* balance(node*);
int getBF(node*);
int getHeight(node*);
int max(int, int);
void inOrder(node*);
void preOrder(node*);
void posOrder(node*);







int main(void){
    srand(time(NULL));
    system("cls||clear");

    node* root = NULL;
    int x;
    for (int i = 0; i < 10; ++i){
        x = rand() % 100;
        root = insert(root, x);
        inOrder(root);
        printf("\n");
    }

    printf("\n");
    return 0;
}






node* newNode(int value){
    node* new = malloc(sizeof(node));
    new->value = value;
    new->height = 1;
    new->left = new->right = NULL;
    return new;
}

node* insert(node* root, int value){
    if (!root) return newNode(value);
    if (value < root->value) root->left = insert(root->left, value);
    if (value > root->value) root->right = insert(root->right, value);
    root->height = 1 + getHeight(root);
    //root = balance(root);
    return root;
}

int max(int a, int b) {
    return (a > b ? a : b);
}

int getHeight(node* root){
    if (!root) return 0;
    if (!root->left) return root->right->height;
    if (!root->right) return root->left->height;
    return max(root->left->height, root->right->height);
}

node* balance(node* root){
    int balancingFactor = getBF(root);
    if (balancingFactor > 1 && getBF(root->right) >= 0){
        return leftRotation(root);
    }
    if (balancingFactor > 1 && getBF(root->right) < 0){
        return rightLeftRotation(root);
    }
    if (balancingFactor < -1 && getBF(root->left) <= 0){
        return rightRotation(root);
    }
    if (balancingFactor < -1 && getBF(root->left) > 0){
        return leftRightRotation(root);
    }
    return root;
}

void inOrder(node* root){
    if (root){
        inOrder(root->left);
        printf("%d[%d] ", root->value, root->height);
        inOrder(root->right);
    }
}

node* leftRotation(node* root){
    if (!root || !root->right) return NULL;
    node* son = root->right;

    root->right = son->left;
    son->left = root;

    son->height = getHeight(son) + 1;
    root->height = getHeight(root) + 1;

    return son;
}

node* rightRotation(node* root){
    if (!root || !root->left) return NULL;
    node* son = root->left;
    
    root->left = son->right;
    son->right = root;

    son->height = getHeight(son) + 1;
    root->height = getHeight(root) + 1;
    return son;
}

node* leftRightRotation(node* root){
    if (root){
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    return NULL;
}

node* rightLeftRotation(node* root){
    if (root){
        root->right = rightRotation(root->right);
        return leftRotation(root); 
    }
    return NULL;
}

int getBF(node* root){
    return (getHeight(root->right) - getHeight(root->left));
}