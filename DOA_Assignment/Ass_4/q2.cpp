#include <iostream>
#include <vector>
using namespace std;

enum Color { RED, BLACK };

class node {
public:
    int key;
    node* left;
    node* right;
    node* parent;
    Color color;

    node(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class rbt {
public:
    node* root;

    rbt() : root(nullptr) {}



// ------------------------------------
    int size(node* n) {
        if (n == nullptr) return 0;
        return 1 + size(n->left) + size(n->right);
    }

    node* searchn(node* n, int key) {
        if (n == nullptr || n->key == key) return n;
        if (key < n->key) return searchn(n->left, key);
        return searchn(n->right, key);
    }

// -------------------------------------




    bool searchRecursively(node* n, int key) {
        if (n == nullptr) return false;
        if (n->key == key) return true;
        if (key < n->key) return searchRecursively(n->left, key);
        return searchRecursively(n->right, key);
    }

    bool search(int key) {
        return searchRecursively(root, key);
    }






// ------------------------------------



    void inorder(node* n, vector<int>& result) {
        if (n != nullptr) {
            inorder(n->left, result);
            result.push_back(n->key);
            inorder(n->right, result);
        }
    }

    vector<int> inorder() {
        vector<int> result;
        inorder(root, result);
        return result;
    }



// -----------------------------

    node* selectn(node* n, int k) {
        int leftSize = (n->left != nullptr) ? size(n->left) : 0;
        if (k == leftSize + 1) {
            return n;
        } else if (k <= leftSize) {
            return selectn(n->left, k);
        } else {
            return selectn(n->right, k - leftSize - 1);
        }
    }
    int select(int k) { // kth smallest element btata hai 
        node* result = selectn(root, k);
        return result ? result->key : -1;
    }



// --------------------------------




    int rankn(node* n, int key) {
        if (n == nullptr) return 0;
        if (key < n->key) {
            return rankn(n->left, key);
        } else if (key > n->key) {
            int leftSize = (n->left != nullptr) ? size(n->left) : 0;
            return leftSize + 1 + rankn(n->right, key);
        } else {
            return size(n->left) + 1;
        }
    }
    int rank(int key) { // kitne elements isse chote hai
        return rankn(root, key);
    }



// ------------------------------

    node* findminN(node* n) {
        while (n && n->left != nullptr) {
            n = n->left;
        }
        return n;
    }

    int findmin() {
        node* n = findminN(root);
        return n ? n->key : -1;
    }



// ---------------------------------------



    node* findmaxN(node* n) {
        while (n && n->right != nullptr) {
            n = n->right;
        }
        return n;
    }
    int findmax() {
        node* n = findmaxN(root);
        return n ? n->key : -1;
    }




// --------------------------------

node* findpredn(node* root, node* n) {
    if (n->left != nullptr) {
        return findmaxN(n->left);
    }

    node* predecessor = nullptr;
    while (root != nullptr) {
        if (n->key > root->key) {
            predecessor = root;
            root = root->right;
        } else if (n->key < root->key) {
            root = root->left;
        } else {
            break;
        }
    }
    return predecessor;
}

node* findsuccn(node* root, node* n) {
    if (n->right != nullptr) {
        return findminN(n->right);
    }

    node* successor = nullptr;
    while (root != nullptr) {
        if (n->key < root->key) {
            successor = root;
            root = root->left;
        } else if (n->key > root->key) {
            root = root->right;
        } else {
            break;
        }
    }
    return successor;
}

int findpred(int key) {
    node* n = searchn(root, key);
    if (!n) return -1;
    node* predecessor = findpredn(root, n);
    return predecessor ? predecessor->key : -1;
}

int findsucc(int key) {
    node* n = searchn(root, key);
    if (!n) return -1;
    node* successor = findsuccn(root, n);
    return successor ? successor->key : -1;
}




// ------------------------------------



    node* insertN(node* n, node* newn) {
        if (n == nullptr) {
            return newn;
        }
        if (newn->key < n->key) {
            n->left = insertN(n->left, newn);
            n->left->parent = n;
        } else if (newn->key > n->key) {
            n->right = insertN(n->right, newn);
            n->right->parent = n;
        }
        return n;
    }



    void fixI(node* n) {
        node* parent = nullptr;
        node* grandparent = nullptr;

        while (n != root && n->color != BLACK && n->parent->color == RED) {
            parent = n->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                node* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    n = grandparent;
                } else {
                    if (n == parent->right) {
                        rotateLeft(parent);
                        n = parent;
                        parent = n->parent;
                    }
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    n = parent;
                }
            } else {
                node* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    n = grandparent;
                } else {
                    if (n == parent->left) {
                        rotateRight(parent);
                        n = parent;
                        parent = n->parent;
                    }
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    n = parent;
                }
            }
        }
        root->color = BLACK;
    }


    void insert(int key) {
        node* newn = new node(key);
        root = insertN(root, newn);
        fixI(newn);
    }




// ------------------------------------
void rotateLeft(node* x) {
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    x->right = T2;

    if (T2 != nullptr) {
        T2->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    x->parent = y;
}

void rotateRight(node* y) {
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    if (T2 != nullptr) {
        T2->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    y->parent = x;
}




// ------------------------------------
    void delet(int key) {
        deletN(root, key);
    }
    
    void transplant(node*& root, node* u, node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void deletN(node*& root, int key) {
        node* n = searchn(root, key);
        if (n == nullptr) return;

        node* y = n;
        node* x;
        node* xParent;
        Color originalColor = y->color;

        if (n->left == nullptr) {
            x = n->right;
            transplant(root, n, n->right);
        } else if (n->right == nullptr) {
            x = n->left;
            transplant(root, n, n->left);
        } else {
            y = findminN(n->right);
            originalColor = y->color;
            x = y->right;
            if (y->parent == n) {
                if (x != nullptr) x->parent = y;
                xParent = y;
            } else {
                transplant(root, y, y->right);
                y->right = n->right;
                y->right->parent = y;
                xParent = y->parent;
            }
            transplant(root, n, y);
            y->left = n->left;
            y->left->parent = y;
            y->color = n->color;
        }

        delete n;

        if (originalColor == BLACK) {
            fixD(root, x, xParent);
        }
    }

    void fixD(node*& root, node* x, node* xParent) {
        while (x != root && (x == nullptr || x->color == BLACK)) {
            if (x == xParent->left) {
                node* w = xParent->right;
                if (w->color == RED) { // Case 4
                    w->color = BLACK;
                    xParent->color = RED;
                    rotateLeft(xParent);
                    w = xParent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) { // Case 3
                    w->color = RED;
                    x = xParent;
                    xParent = xParent->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK) { // Case 5
                        if (w->left != nullptr) w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = xParent->right;
                    }
                    // Case 6
                    w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->right != nullptr) w->right->color = BLACK;
                    rotateLeft(xParent);
                    x = root;
                }
            } else {
                node* w = xParent->left;
                if (w->color == RED) { // Case 4
                    w->color = BLACK;
                    xParent->color = RED;
                    rotateRight(xParent);
                    w = xParent->left;
                }
                if ((w->right == nullptr || w->right->color == BLACK) &&
                    (w->left == nullptr || w->left->color == BLACK)) { // Case 3
                    w->color = RED;
                    x = xParent;
                    xParent = xParent->parent;
                } else {
                    if (w->left == nullptr || w->left->color == BLACK) { // Case 5
                        if (w->right != nullptr) w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = xParent->left;
                    }
                    // Case 6
                    w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->left != nullptr) w->left->color = BLACK;
                    rotateRight(xParent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->color = BLACK; 
    }

    

};





// ------------------------------------


int main() {
    rbt rbt;

    rbt.insert(20);
    rbt.insert(15);
    rbt.insert(25);
    rbt.insert(10);
    rbt.insert(5);

    vector<int> inorder = rbt.inorder();
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Min: " << rbt.findmin() << endl;
    cout << "Max: " << rbt.findmax() << endl;

    cout << "Predecessor of 15: " << rbt.findpred(15) << endl;
    cout << "Successor of 15: " << rbt.findsucc(15) << endl;

    rbt.delet(15);

    inorder = rbt.inorder();
    cout << "In-order after deletion: ";
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
