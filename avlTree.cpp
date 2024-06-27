#include <iostream>

int max(int a, int b){
    return (a > b) ? a : b;
}

class Node{
    public:
        int value;
        int height = 1;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

    int getHeight(Node* node){
        return node ? node->height : 0;
    }

    int getHeight(){
        return max(getHeight(this->left), getHeight(this->right)) + 1;
    }

    int getBF(Node* node){
        return node ? node->right->getHeight() - node->left->getHeight() : 0;
    }
    int getBF(){
        return getBF(this);
    }

    Node* leftRotation(Node* node){
        if (!node || !node->right) return node;
        Node* son = node->right;

        node->right = son->left;
        son->left = node;

        son->height = son->getHeight();
        node->height = node->getHeight();

        return son;
    }
    Node* leftRotation(){
        return leftRotation(this);
    }

    Node* rightRotation(Node* node){
        if (!node || !node->left) return node;
        Node* son = node->left;

        node->left = son->right;
        son->right = node;

        son->height = son->getHeight();
        node->height = node->getHeight();

        return son;
    }
    Node* rightRotation(){
        return rightRotation(this);
    }
};

Node* newNode(Node* root, int value){
    Node* New = new Node;
    New->value = value;
    New->parent = root;
    return New;
}

class Tree{
    public:
      Node* root = nullptr;
      int size = 0;
      int height = 0;

    Node* insert(Node* parent, int value){
        Node* New = newNode(parent, value);
        if (!parent){
            return New;
        }
        if (value < parent->value){
            parent->left = insert(parent->left, value);
        }
        else if (value > parent->value){
            parent->right = insert(parent->right, value);
        }
        ++parent->height;
        return parent;
    }
    void insert(int value){
        this->root = insert(this->root, value);
        ++this->size;
        this->height = this->root->height;
    }

    void inOrder(Node* parent){
        if (parent){
            inOrder(parent->left);
            std::cout << parent->value << " ";
            inOrder(parent->right);
        }
    }
    void inOrder(){
        inOrder(this->root);
    }

    Node* balance(Node* parent){
        if (!parent) return parent;
        int balancingFactor = parent->getBF();
        if (balancingFactor > 1 && parent->right->getBF() >= 0){
            return parent->leftRotation();
        }
        if (balancingFactor > 1 && parent->right->getBF() < 0){
            parent->right = parent->right->rightRotation();
            return parent->leftRotation();
        }
        if (balancingFactor < -1 && parent->right->getBF() <= 0){
            return parent->rightRotation();
        }
        if (balancingFactor < -1 && parent->right->getBF() > 0){
            parent->left = parent->left->leftRotation();
            return parent->rightRotation();
        }
        return parent;
    }

};


int main(void){
    system("cls||clear");

    Tree tree;
    tree.insert(10);
    for (int i = 0 + 7; i < 7 + 7; ++i){
        tree.insert(i);
    }
    tree.root->leftRotation();
    tree.inOrder();

    std::cout << "\n";
    return 0;
}