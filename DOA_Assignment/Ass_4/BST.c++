#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int val) {
        key = val;
        left = right = NULL;
    }
};

Node* insert(Node* node, int key) {
    if (node == NULL) 
        return new Node(key);    

    if (node->key == key) 
        return node;

    if (node->key < key) 
        node->right = insert(node->right, key);
    else 
        node->left = insert(node->left, key);
    
    return node;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

Node* findminimum(Node* root) {
    if (root->left == NULL)
        return root;
    return findminimum(root->left);
}

Node* findmaximum(Node* root) {
    if (root->right == NULL)
        return root;
    return findmaximum(root->right); 
}

Node* findSuccessor(Node* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

Node* findPredecessor(Node* curr) { 
    curr = curr->left; 
    while (curr != NULL && curr->right != NULL) 
        curr = curr->right;
    return curr;
}

Node* deleteNode(Node* root, int x) {
    if (root == NULL)
        return root;
    if (root->key > x)
        root->left = deleteNode(root->left, x);
    else if (root->key < x)
        root->right = deleteNode(root->right, x); 
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* succ = findSuccessor(root);
        root->key = succ->key;
        root->right = deleteNode(root->right, succ->key);
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
Node* searchPredecessor(Node* root, int key) {
    if ( root->key == key)
        return findPredecessor(root);

    if (root->key < key)
        return searchPredecessor(root->right, key);

    return searchPredecessor(root->left, key);
}
Node* searchSuccessor(Node* root, int key) {
    if (root->key == key)
        return findSuccessor(root);

    if (root->key < key)
        return searchSuccessor(root->right, key);

    return searchSuccessor(root->left, key);
}
int main() {
    Node* root = NULL; // Initialize root pointer
    //        50
    //      /    \
    //     /      \
    //   30        70
    //   / \       / \
    // 20   40   60  80
    
    // Insert the nodes into the tree
    root = insert(root, 50); // Corrected to use the root pointer
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    // Print inorder traversal
    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    // Delete nodes
    root = deleteNode(root, 80);
    root = deleteNode(root, 30);
    root = deleteNode(root, 50);

    cout << "Inorder traversal after deletions: ";
    inorder(root);
    cout << endl;

    cout << "Minimum value: " << findminimum(root)->key << endl;
    cout << "Maximum value: " << findmaximum(root)->key << endl;

    cout << "Predecessor of 60"  << ": " << searchPredecessor(root,60)->key << endl;
    cout << "Successor of 60"   << ": " << searchSuccessor(root,60)->key << endl;
    return 0;
}
