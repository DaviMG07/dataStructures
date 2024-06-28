
#include <iostream>

template<typename anyType, typename anotherType>
auto max(anyType x, anotherType y){
    return (x > y) ? x : y;
}

class Node{
    public:
        int value;
        int height;
        Node* left;
        Node* right;
    
    Node* leftRotation(Node* root){
        if (!root || !root->right) return nullptr;
        Node* son = root->right;

        root->right = son->left;
        son->left = root;

        root->getHeight();
        son->getHeight();

        return son;
    }
    Node* leftRotation(){
        return leftRotation(this);
    }
    Node* rightRotation(Node* root){
        if (!root || !root->left) return nullptr;
        Node* son = root->left;
        root->left = son->right;
        son->right = root;

        root->getHeight();
        son->getHeight();

        return son;
    }
    Node* rightRotation(){
        return rightRotation(this);
    }

    int getHeight(Node* root){
        return root ? root->height : 0;
    }
    int getHeight(){
        this->height = max(getHeight(this->left), getHeight(this->right)) + 1;
        return this->height;
    }

    void print(){
        printf("%d(%d)", this->value, this->height);
    }

    int getBalance(){
        return (getHeight(this->right) - getHeight(this->left));
    }

    Node* balance(Node* root){
        if (!root) return nullptr;
        int bfactor = root->getBalance();

        if (bfactor > 1 && root->right->getBalance() >= 0){
            return leftRotation(root);
        }
        if (bfactor > 1 && root->right->getBalance() < 0){
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
        if (bfactor < -1 && root->left->getBalance() <= 0){
            return rightRotation(root);
        }
        if (bfactor < -1 && root->left->getBalance() > 0){
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
        root->getHeight();
        return root;
    }
    Node* balance(){
        return balance(this);
    }

    Node* getMin(){
        Node* current = this;
        while (current->left){
            current = current->left;
        }
        return current;
    }
};

Node* newNode(int value){
    Node* New = new Node;
    New->value = value;
    New->height = 1;
    New->left = New->right = nullptr;
    return New;
}

class Tree{
    public:
        Node* root = nullptr;
        Node* right = nullptr;
        Node* left = nullptr;


    Node* insert(Node* parent, int value){
        Node* New = newNode(value);
        if (!parent){
            return New;
        }
        if (value < parent->value){
            parent->left = insert(parent->left, value);
        }
        else if (value > parent->value){
            parent->right = insert(parent->right, value);
        }
        parent->getHeight();
        return parent;
    }
    void insert(int value){
        this->root = insert(this->root, value);
        this->right = this->root->right;
        this->left = this->root->left;
        this->balance();
    }

    void inOrder(Node* parent){
        if (parent){
            inOrder(parent->left);
            parent->print();
            std::cout << " ";
            inOrder(parent->right);
        }
    }
    void inOrder(){
        inOrder(this->root);
        std::cout << "\n";
    }

    void preOrder(Node* parent){
        if (parent){
            parent->print();
            std::cout << " ";
            preOrder(parent->left);
            preOrder(parent->right);
        }
    }
    void preOrder(){
        preOrder(this->root);
        std::cout << "\n";
    }

    void posOrder(Node* parent){
        if (parent){
            posOrder(parent->left);
            posOrder(parent->right);
            parent->print();
            std::cout << " ";
        }
    }
    void posOrder(){
        posOrder(this->root);
        std::cout << "\n";
    }

    void balance(){
        this->root = this->root->balance();
    }

    Node* remove(Node* parent, int value){
        if (!parent) return nullptr;
        if (parent->value < value){
            return remove(parent->left, value);
        }
        if (parent->value > value){
            return remove(parent->right, value);
        }
        if (parent->value == value){
            Node* minimum = parent->right->getMin();
            parent->value = minimum->value;
            free(minimum);
        }
        return parent;
    }
    void remove(int value){
        this->root = remove(this->root, value);
        this->balance();
    }
};

int main(void){
    srand(time(nullptr));
    system("cls||clear");

    Tree tree;
    for (int i = 0; i < 100; ++i){
        tree.insert(rand() % 10);
    }
    tree.remove(10);
    tree.inOrder();
    tree.posOrder();
    tree.preOrder();

    std::cout << "\n";
    return 0;
}