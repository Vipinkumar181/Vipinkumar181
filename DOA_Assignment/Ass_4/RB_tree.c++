#include <bits/stdc++.h>
using namespace std;

///////////////////
struct Node {
    int key;
    Node* left;
    Node* right;
    char colour;
    Node* parent;

    Node(int val) {
        key = val;
        left = NULL;
        right = NULL;
        colour = 'R';
        parent = NULL;
    }

    Node* sibling() {
        if (parent == nullptr)
            return nullptr;
        if (this == parent->left)
            return parent->right;
        return parent->left;
    }
};

Node* root = NULL;  // Set the global root to NULL initially
bool ll; // Left-Left Rotation flag
bool rr; // Right-Right Rotation flag
bool lr; // Left-Right Rotation flag
bool rl; // Right-Left Rotation flag

/////////////////////////////////////

struct Node* rotateLeft(Node* node) {
    Node* x = node->right;
    Node* y = x->left;
    x->left = node;
    node->right = y;
    node->parent = x;
    if (y != nullptr)
        y->parent = node;
    return x;
}

struct Node* rotateRight(Node* node) {
    Node* x = node->left;
    Node* y = x->right;
    x->right = node;
    node->left = y;
    node->parent = x;
    if (y != nullptr)
        y->parent = node;
    return x;
}

struct Node* insert(Node* root, int key) {
    bool flag = false; // Flag to check RED-RED conflict
    if (root == nullptr)
        return new Node(key);
    else if (key < root->key) {
        root->left = insert(root->left, key);
        root->left->parent = root;
        if (root != ::root) {
            if (root->colour == 'R' && root->left->colour == 'R')
                flag = true;
        }
    } else {
        root->right = insert(root->right, key);
        root->right->parent = root;
        if (root != ::root) {
            if (root->colour == 'R' && root->right->colour == 'R')
                flag = true;
        }
    }

    // Perform rotations
    if (ll) {
        root = rotateLeft(root);
        root->colour = 'B';
        root->left->colour = 'R';
        ll = false;
    } else if (rr) {
        root = rotateRight(root);
        root->colour = 'B';
        root->right->colour = 'R';
        rr = false;
    } else if (rl) {
        root->right = rotateRight(root->right);
        root->right->parent = root;
        root = rotateLeft(root);
        root->colour = 'B';
        root->left->colour = 'R';
        rl = false;
    } else if (lr) {
        root->left = rotateLeft(root->left);
        root->left->parent = root;
        root = rotateRight(root);
        root->colour = 'B';
        root->right->colour = 'R';
        lr = false;
    }

    // Handle RED-RED conflicts
    if (flag) {
        if (root->parent->right == root) {
            if (root->parent->left == nullptr || root->parent->left->colour == 'B') {
                if (root->left != nullptr && root->left->colour == 'R')
                    rl = true;
                else if (root->right != nullptr && root->right->colour == 'R')
                    ll = true;
            } else {
                root->parent->left->colour = 'B';
                root->colour = 'B';
                if (root->parent != ::root)
                    root->parent->colour = 'R';
            }
        } else {
            if (root->parent->right == nullptr || root->parent->right->colour == 'B') {
                if (root->left != nullptr && root->left->colour == 'R')
                    rr = true;
                else if (root->right != nullptr && root->right->colour == 'R')
                    lr = true;
            } else {
                root->parent->right->colour = 'B';
                root->colour = 'B';
                if (root->parent != ::root)
                    root->parent->colour = 'R';
            }
        }
        flag = false;
    }
    return root;
}

void insertnode(int data) {
    if (root == nullptr) {
        root = new Node(data);
        root->colour = 'B';
    } else
        root = insert(root, data);
}

////////////////////////////////////////////////
struct Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}
//////////////////////////////////////////////////
struct Node* findminimum(Node* root) {
    if (root->left == NULL)
        return root;
    return findminimum(root->left);
}

struct Node* findmaximum(Node* root) {
    if (root->right == NULL)
        return root;
    return findmaximum(root->left);
}

struct Node* findSuccessor(Node* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

struct Node* findPredessor(Node* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

//////////////////////////////////////////////////
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " (" << root->colour << ") ";
        inorder(root->right);
    }
}

//////////////////////////////////////////////////
void fixDoubleBlack(Node* x) {
    if (x == root)
        return;

    Node* sibling = (x->parent->left == x) ? x->parent->right : x->parent->left;
    Node* parent = x->parent;

    if (sibling == NULL) {
        fixDoubleBlack(parent);
    } else {
        if (sibling->colour == 'R') {
            parent->colour = 'R';
            sibling->colour = 'B';
            if (sibling == parent->left) {
                root = rotateRight(parent);
            } else {
                root = rotateLeft(parent);
            }
            fixDoubleBlack(x);
        } else {
            if ((sibling->left != NULL && sibling->left->colour == 'R') || 
                (sibling->right != NULL && sibling->right->colour == 'R')) {
                if (sibling->left != NULL && sibling->left->colour == 'R') {
                    if (sibling == parent->left) {
                        sibling->left->colour = sibling->colour;
                        sibling->colour = parent->colour;
                        root = rotateRight(parent);
                    } else {
                        sibling->left->colour = parent->colour;
                        root = rotateRight(sibling);
                        root = rotateLeft(parent);
                    }
                } else {
                    if (sibling == parent->left) {
                        sibling->right->colour = parent->colour;
                        root = rotateLeft(sibling);
                        root = rotateRight(parent);
                    } else {
                        sibling->right->colour = sibling->colour;
                        sibling->colour = parent->colour;
                        root = rotateLeft(parent);
                    }
                }
                parent->colour = 'B';
            } else {
                sibling->colour = 'R';
                if (parent->colour == 'B')
                    fixDoubleBlack(parent);
                else
                    parent->colour = 'B';
            }
        }
    }
}


struct Node* findReplacement(Node* node) {
    if (node->left != NULL && node->right != NULL)
        return findSuccessor(node->right);
    if (node->left == NULL && node->right == NULL)
        return NULL;
    return (node->left != NULL) ? node->left : node->right;
}

void deleteNode(Node* v) {
    Node* u = findReplacement(v);
    bool uvBlack = ((u == NULL || u->colour == 'B') && (v->colour == 'B'));
    Node* parent = v->parent;

    if (u == NULL) { // Leaf node
        if (v == root) {
            root = NULL;
        } else {
            if (uvBlack) {
                fixDoubleBlack(v);
            } else {
                if (v->sibling() != NULL)
                    v->sibling()->colour = 'R';
            }
            if (v->parent->left == v)
                v->parent->left = NULL;
            else
                v->parent->right = NULL;
        }
        delete v;
        return;
    }

    if (v->left == NULL || v->right == NULL) {
        if (v == root) {
            v->key = u->key;
            v->left = v->right = NULL;
            delete u;
        } else {
            if (v->parent->left == v)
                v->parent->left = u;
            else
                v->parent->right = u;
            u->parent = v->parent;
            if (uvBlack) {
                fixDoubleBlack(u);
            } else {
                u->colour = 'B';
            }
            delete v;
        }
        return;
    }

    Node* successor = findSuccessor(v->right);
    swap(v->key, successor->key);
    deleteNode(successor);
}


/////////////////////////////////////////////////////////

void deleteByValue(int key) {
    Node* node = search(root, key);
    if (node == nullptr) {
        cout << "Node with key " << key << " not found." << endl;
        return;
    }
    deleteNode(node);
}
int main() {
    // Insert the nodes into the tree
    insertnode(50);
    insertnode(30);
    insertnode(70);
    insertnode(20);
    insertnode(40);
    insertnode(60);
    insertnode(80);

    // Print inorder traversal with node colours
    inorder(root);
    cout<<endl;
    deleteByValue(80);
    deleteByValue(30);
    deleteByValue(50);

    inorder(root);
    return 0;
}
