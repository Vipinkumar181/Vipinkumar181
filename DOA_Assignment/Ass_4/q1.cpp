#include <iostream>
#include <vector>
using namespace std;

class node {
public:
    int key;
    int size;  
    node* l;
    node* r;

    node(int key) : key(key), size(1), l(nullptr), r(nullptr) {}
};

class BinarySearchTree {
public:
    node* root;

    BinarySearchTree() : root(nullptr) {}

    int size(node* n) {
        return n == nullptr ? 0 : n->size;
    }

    void updateSize(node* n) {
        if (n != nullptr) {
            n->size = size(n->l) + size(n->r) + 1;
        }
    }

    void insert(int key) {
        root = insertRecursively(root, key);
    }

    node* insertRecursively(node* n, int key) {
        if (n == nullptr) {
            return new node(key);
        }
        if (key < n->key) {
            n->l = insertRecursively(n->l, key);
        } else if (key > n->key) {
            n->r = insertRecursively(n->r, key);
        }
        updateSize(n);  
        return n;
    }

    bool search(int key) {
        node* current = root;
        while (current != nullptr) {
            if (key == current->key) {
                return true;
            } else if (key < current->key) {
                current = current->l;
            } else {
                current = current->r;
            }
        }
        return false;
    }

    void inorderTraversal(node* n, vector<int>& result) {
        if (n != nullptr) {
            inorderTraversal(n->l, result);
            result.push_back(n->key);
            inorderTraversal(n->r, result);
        }
    }

    vector<int> inorderTraversal() {
        vector<int> result;
        inorderTraversal(root, result);
        return result;
    }

    int findMinimum() {
        if (root == nullptr) return -1;
        node* current = root;
        while (current->l != nullptr) {
            current = current->l;
        }
        return current->key;
    }

    int findMaximum() {
        if (root == nullptr) return -1;
        node* current = root;
        while (current->r != nullptr) {
            current = current->r;
        }
        return current->key;
    }

    node* deleten(node* n, int key) {
        if (n == nullptr) return n;

        if (key < n->key) {
            n->l = deleten(n->l, key);
        } else if (key > n->key) {
            n->r = deleten(n->r, key);
        } else {
            if (n->l == nullptr) {
                node* temp = n->r;
                delete n;
                return temp;
            } else if (n->r == nullptr) {
                node* temp = n->l;
                delete n;
                return temp;
            }

            node* temp = findmin(n->r);
            n->key = temp->key;
            n->r = deleten(n->r, temp->key);
        }
        updateSize(n); 
        return n;
    }

    void deleteKey(int key) {
        root = deleten(root, key);
    }

    node* findmax(node* n) {
        while (n->r != nullptr) {
            n = n->r;
        }
        return n;
    }

    node* findmin(node* n) {
        while (n->l != nullptr) {
            n = n->l;
        }
        return n;
    }

    node* findpredn(node* root, node* n) {
        if (n->l != nullptr) {
            return findmax(n->l);
        }
        node* predecessor = nullptr;
        while (root != nullptr) {
            if (n->key > root->key) {
                predecessor = root;
                root = root->r;
            } else if (n->key < root->key) {
                root = root->l;
            } else {
                break;
            }
        }
        return predecessor;
    }

    node* findsuccn(node* root, node* n) {
        if (n->r != nullptr) {
            return findmin(n->r);
        }
        node* successor = nullptr;
        while (root != nullptr) {
            if (n->key < root->key) {
                successor = root;
                root = root->l;
            } else if (n->key > root->key) {
                root = root->r;
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

    node* searchn(node* n, int key) {
        if (n == nullptr || n->key == key) return n;
        if (key < n->key) return searchn(n->l, key);
        return searchn(n->r, key);
    }

    int select(node* n, int k) {
        if (n == nullptr) return -1;  

        int leftSize = size(n->l);

        if (leftSize + 1 == k) {
            return n->key; 
        } else if (leftSize >= k) {
            return select(n->l, k);  
        } else {
            return select(n->r, k - leftSize - 1); 
        }
    }

    int select(int k) {
        return select(root, k);
    }

    int rank(node* n, int key) {
        if (n == nullptr) return 0;

        if (key < n->key) {
            return rank(n->l, key);  
        } else if (key > n->key) {
            return 1 + size(n->l) + rank(n->r, key); }
        else{ 
            return size(n->l); 
        }
    }

    int rank(int key) {
        return rank(root, key);
    }
};

int main() {
    BinarySearchTree bst;

    bst.insert(20);
    bst.insert(15);
    bst.insert(25);
    bst.insert(10);
    bst.insert(5);

    vector<int> inorder = bst.inorderTraversal();
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl;


    cout << "Min: " << bst.findMinimum() << endl;
    cout << "Max: " << bst.findMaximum() << endl;

    
    cout << "Predecessor of 15: " << bst.findpred(15) << endl;
    cout << "Successor of 15: " << bst.findsucc(15) << endl;

    bst.deleteKey(15);
    inorder = bst.inorderTraversal();
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl;

    cout << "2nd smallest element: " << bst.select(2) << endl;
    cout << "Rank of 10: " << bst.rank(10) << endl;

    return 0;
}
