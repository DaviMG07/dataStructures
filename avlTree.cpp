
#include <iostream>

template<typename anyType, typename anotherType>
auto max(anyType x, anotherType y){
    return (x > y) ? x : y;
}

class Node {
    public:
        int value;
        int height;
        Node* left;
        Node* right;
    
    // Left rotation on a given node
    Node* leftRotation(Node* root) {
        if (!root || !root->right) return nullptr;
        Node* son = root->right;

        root->right = son->left;
        son->left = root;

        root->getHeight();  // Update the height of the original root
        son->getHeight();   // Update the height of the new root

        return son;
    }
    // Left rotation on the current node
    Node* leftRotation() {
        return leftRotation(this);
    }

    // Right rotation on a given node
    Node* rightRotation(Node* root) {
        if (!root || !root->left) return nullptr;
        Node* son = root->left;
        root->left = son->right;
        son->right = root;

        root->getHeight();  // Update the height of the original root
        son->getHeight();   // Update the height of the new root

        return son;
    }
    // Right rotation on the current node
    Node* rightRotation() {
        return rightRotation(this);
    }

    // Calculate the height of a given node
    int getHeight(Node* root) {
        if (!root) {
            return 0;
        }
        if (root->isLeaf()) {
            return 1;
        }
        return max(getHeight(root->right), getHeight(root->left)) + 1;
    }
    // Update and return the height of the current node
    int getHeight() {
        this->height = getHeight(this);
        return this->height;
    }

    // Recursively update the height of the subtree rooted at a given node
    void updateHeight(Node* root) {
        if (root) {
            root->getHeight();
            updateHeight(root->left);
            updateHeight(root->right);
        }
    }
    // Recursively update the height of the subtree rooted at the current node
    void updateHeight() {
        updateHeight(this);
    }

    // Print the value and height of the current node
    void print() {
        printf("%d(%d)", this->value, this->height);
    }

    // Calculate and return the balance factor (height of right subtree - height of left subtree)
    int getBalance() {
        return (getHeight(this->right) - getHeight(this->left));
    }

    // Balance the subtree rooted at a given node
    Node* balance(Node* root) {
        if (!root) return nullptr;
        root->updateHeight();  // Update the height of the current node
        int bfactor = root->getBalance();

        if (bfactor > 1) {
            // Right Left Case
            if (root->right->getBalance() < 0)
                root->right = rightRotation(root->right);
            // Right Right Case
            return leftRotation(root);
        }
        // Left heavy case
        if (bfactor < -1) {
            // Left Right Case
            if (root->left->getBalance() > 0)
                root->left = leftRotation(root->left);
            // Left Left Case
            return rightRotation(root);
        }
        root->updateHeight();
        return root;
    }
    // Balance the subtree rooted at the current node
    Node* balance() {
        Node* aux = balance(this);
        aux->left = balance(aux->left);
        aux->right = balance(aux->right);
        return aux;
    }

    // Find the node with the minimum value in the subtree rooted at the current node
    Node* getMin() {
        Node* current = this;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    // Check if the current node is a leaf node
    bool isLeaf() {
        return (!this->left && !this->right);
    }
};


Node* newNode(int value){
    Node* New = new Node;
    New->value = value;
    New->height = 1;
    New->left = New->right = nullptr;
    return New;
}

class Tree {
    public:
        Node* root = nullptr;
        Node* right = nullptr;
        Node* left = nullptr;

    // Helper function to insert a node with a given value into the tree
    Node* insert(Node* parent, int value) {
        Node* New = newNode(value); // Create a new node with the given value
        if (!parent) {
            return New; // If the parent is null, return the new node
        }
        if (value < parent->value) {
            parent->left = insert(parent->left, value); // Insert into the left subtree
        } else if (value > parent->value) {
            parent->right = insert(parent->right, value); // Insert into the right subtree
        }
        parent->getHeight(); // Update the height of the parent node
        return parent; // Return the parent node
    }

    // Public method to insert a value into the tree
    void insert(int value) {
        this->root = insert(this->root, value); // Insert the value starting from the root
        this->right = this->root->right; // Update the right pointer of the tree
        this->left = this->root->left; // Update the left pointer of the tree
        this->balance(); // Balance the tree after insertion
    }

    // Helper function for in-order traversal of the tree
    void inOrder(Node* parent) {
        if (parent) {
            inOrder(parent->left); // Traverse the left subtree
            parent->print(); // Print the current node
            std::cout << " ";
            inOrder(parent->right); // Traverse the right subtree
        }
    }

    // Public method to perform in-order traversal starting from the root
    void inOrder() {
        inOrder(this->root);
        std::cout << "\n";
    }

    // Helper function for pre-order traversal of the tree
    void preOrder(Node* parent) {
        if (parent) {
            parent->print(); // Print the current node
            std::cout << " ";
            preOrder(parent->left); // Traverse the left subtree
            preOrder(parent->right); // Traverse the right subtree
        }
    }

    // Public method to perform pre-order traversal starting from the root
    void preOrder() {
        preOrder(this->root);
        std::cout << "\n";
    }

    // Helper function for post-order traversal of the tree
    void posOrder(Node* parent) {
        if (parent) {
            posOrder(parent->left); // Traverse the left subtree
            posOrder(parent->right); // Traverse the right subtree
            parent->print(); // Print the current node
            std::cout << " ";
        }
    }

    // Public method to perform post-order traversal starting from the root
    void posOrder() {
        posOrder(this->root);
        std::cout << "\n";
    }

    // Balance the tree by balancing the root
    void balance() {
        this->root = this->root->balance();
    }

    // Helper function to remove a node with a given value from the tree
    Node* remove(Node* parent, int value) {
        if (!parent) return nullptr; // If the parent is null, return null
        if (value < parent->value) {
            parent->left = remove(parent->left, value); // Remove from the left subtree
            return parent;
        }
        if (value > parent->value) {
            parent->right = remove(parent->right, value); // Remove from the right subtree
            return parent;
        }
        if (parent->isLeaf()) {
            delete parent; // If the node is a leaf, delete it
            return nullptr;
        }
        if (!parent->left) {
            Node* temp = parent->right; // If no left child, replace with right child
            delete parent;
            return temp;
        }
        if (!parent->right) {
            Node* temp = parent->left; // If no right child, replace with left child
            delete parent;
            return temp;
        }

        // Find the maximum value node in the left subtree
        Node* temp = parent->left;
        Node* placeholder = parent;
        while (temp->left) {
            placeholder = temp;
            temp = temp->left;
        }

        parent->value = temp->value; // Replace the value of the current node

        if (placeholder != parent) {
            placeholder->left = remove(placeholder->left, temp->value); // Remove the node in the left subtree
        } else {
            parent->right = remove(parent->right, temp->value); // Remove the node in the right subtree
        }
        parent->balance(); // Balance the tree
        return parent; // Return the parent node
    }

    // Public method to remove a value from the tree
    void remove(int value) {
        this->root = remove(this->root, value); // Remove the value starting from the root
        this->balance(); // Balance the tree after removal
    }
};


int main(void){
    srand(time(nullptr));
    system("cls||clear");

    Tree tree;
    for (int i = 0; i < 100; ++i){
        tree.insert(rand() % 7);
    }
    tree.inOrder();
    tree.remove(0);
    tree.root->updateHeight();
    tree.inOrder();
    tree.posOrder();
    tree.preOrder();

    std::cout << "\n";
    return 0;
}