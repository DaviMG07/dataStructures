#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int value;
    int height;
    int depth;
    struct Node* left;
    struct Node* right;
} node;

node* newNode(int);
node* insert(node*, int);
node* delete(node*, int);
node* search(node*, int);
node* minimum(node*);
void inOrder(node*);

int getHeight(node*);
int max(int, int);






int main(void){
    srand(time(NULL));
    system("cls||clear");

    node* root = NULL;
    int x, first;

    for (int i = 0; i < 15; ++i){
        x = rand() % 100;
        if (!i) first = x;
        root = insert(root, x);
    }

    inOrder(root);

    node* research = search(root->left, root->left->value);

    node* min = minimum(research);

    printf("\nsearched: %d\n", research ? research->value : -1);

    printf("\nminimum value: %d\n", min ? min->value : -1);
    
    while (root){
        root = delete(root, root->value);
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
    new->depth = 1;
    new->left = NULL;
    new->right = NULL;
    return new;
}

node* insert(node* root, int value){
    if (!root) return newNode(value);
    if (value < root->value){
        root->left = insert(root->left, value);
        root->left->depth = root->depth + 1;
    }
    else if (value > root->value) {
        root->right = insert(root->right, value);
        root->right->depth = root->depth + 1;
    }
    ++root->height;
    return root;
}

void inOrder(node* root){
    if (root){
        inOrder(root->left);
        printf("%d[%d, %d] ", root->value, root->height, root->depth);
        inOrder(root->right);
    }
}

node* search(node* root, int value){
    if (!root){
        return NULL;
    }
    if (root->value == value) return root;
    if (value < root->value) return search(root->left, value);
    if (value >= root->value) return search(root->right, value);
    return NULL;
}

node* minimum(node* root){
    if (!root) return NULL;
    node* current = root;
    if (root->left) return minimum(root->left);
    else return root;
}

node* delete(node* root, int value){
    if (!root) 
        return NULL;
    if (value < root->value) 
        root->left = delete(root->left, value);

    else if (value > root->value) 
        root->right = delete(root->right, value);

    else {
        if (!root->left){
            node* current = root->right;
            free(root);
            return current;
        }
        if (!root->right){
            node* current = root->left;
            free(root);
            return current;
        }

        node* current = minimum(root->right);
        root->value = current->value;
        root->right = delete(root->right, root->value);
    }
    return root;
}

int getHeight(node* root){
    return max(root->right->height, root->left->height);
}

int max(int a, int b){
    return (a > b ? a : b);
}
