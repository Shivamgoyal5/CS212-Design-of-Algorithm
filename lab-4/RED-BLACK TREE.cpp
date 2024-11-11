#include <bits/stdc++.h>
using namespace std;

enum Color { RED, BLACK };

class RBTNode {
public:
    int key;
    RBTNode *leftCh, *rightCh, *parent;
    Color color;
    int size; 

    RBTNode(int k) : key(k), leftCh(nullptr), rightCh(nullptr), parent(nullptr), color(RED), size(1) {}
};

class RBTree {
    private:
        RBTNode* root;
        RBTNode* NIL;  

        void leftChRotate(RBTNode* x) {
            RBTNode* y = x->rightCh;
            x->rightCh = y->leftCh;
            if (y->leftCh != NIL) y->leftCh->parent = x;
            y->parent = x->parent;
            if (x->parent == NIL) root = y;
            else if (x == x->parent->leftCh) x->parent->leftCh = y;
            else x->parent->rightCh = y;
            y->leftCh = x;
            x->parent = y;
            y->size = x->size;
            x->size = x->leftCh->size + x->rightCh->size + 1;
        }

        void rightChRotate(RBTNode* y) {
            RBTNode* x = y->leftCh;
            y->leftCh = x->rightCh;
            if (x->rightCh != NIL) x->rightCh->parent = y;
            x->parent = y->parent;
            if (y->parent == NIL) root = x;
            else if (y == y->parent->rightCh) y->parent->rightCh = x;
            else y->parent->leftCh = x;
            x->rightCh = y;
            y->parent = x;
            x->size = y->size;
            y->size = y->leftCh->size + y->rightCh->size + 1;
        }

        void insertRB(RBTNode* z) {
            while (z->parent->color == RED) {
                if (z->parent == z->parent->parent->leftCh) {
                    RBTNode* y = z->parent->parent->rightCh;
                    if (y->color == RED) {
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                    } else {
                        if (z == z->parent->rightCh) {
                            z = z->parent;
                            leftChRotate(z);
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        rightChRotate(z->parent->parent);
                    }
                } else {
                    RBTNode* y = z->parent->parent->leftCh;
                    if (y->color == RED) {
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                    } else {
                        if (z == z->parent->leftCh) {
                            z = z->parent;
                            rightChRotate(z);
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        leftChRotate(z->parent->parent);
                    }
                }
                if (z == root) break;
            }
            root->color = BLACK;
        }

        void transplant(RBTNode* u, RBTNode* v) {
            if (u->parent == NIL) root = v;
            else if (u == u->parent->leftCh) u->parent->leftCh = v;
            else u->parent->rightCh = v;
            v->parent = u->parent;
        }

        void deleteFixup(RBTNode* x) {
            while (x != root && x->color == BLACK) {
                if (x == x->parent->leftCh) {
                    RBTNode* w = x->parent->rightCh;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        leftChRotate(x->parent);
                        w = x->parent->rightCh;
                    }
                    if (w->leftCh->color == BLACK && w->rightCh->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    } else {
                        if (w->rightCh->color == BLACK) {
                            w->leftCh->color = BLACK;
                            w->color = RED;
                            rightChRotate(w);
                            w = x->parent->rightCh;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->rightCh->color = BLACK;
                        leftChRotate(x->parent);
                        x = root;
                    }
                } else {
                    RBTNode* w = x->parent->leftCh;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        rightChRotate(x->parent);
                        w = x->parent->leftCh;
                    }
                    if (w->rightCh->color == BLACK && w->leftCh->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    } else {
                        if (w->leftCh->color == BLACK) {
                            w->rightCh->color = BLACK;
                            w->color = RED;
                            leftChRotate(w);
                            w = x->parent->leftCh;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->leftCh->color = BLACK;
                        rightChRotate(x->parent);
                        x = root;
                    }
                }
            }
            x->color = BLACK;
        }

        RBTNode* mini(RBTNode* node) const {
            while (node->leftCh != NIL){
                 node = node->leftCh;
            }
            return node;
        }

        RBTNode* maxi(RBTNode* node) const {
            while (node->rightCh != NIL) {
                node = node->rightCh;
            }
            return node;
        }

        void inorderTraverse(RBTNode* node) const {
            if (node != NIL) {
                inorderTraverse(node->leftCh);
                cout<<node->key<<" ";
                inorderTraverse(node->rightCh);
            }
        }

        RBTNode* selectRB(RBTNode* node, int k) const {
            if (node == nullptr){
                return nullptr;
            }
            int leftSize = (node->leftCh != nullptr) ? node->leftCh->size : 0;
            if (leftSize == k) {
                return node;
            }
            if (leftSize > k) {
                return selectRB(node->leftCh, k);
            }
            return selectRB(node->rightCh, k - leftSize - 1);
        }

        int rankRB(RBTNode* node, int key) const {
                if (node == nullptr){
                    return 0;
                }
                if (key < node->key){
                    return rankRB(node->leftCh, key);
                } 
                int leftSize = (node->leftCh != nullptr) ? node->leftCh->size : 0;
                if (key == node->key){
                    return leftSize; 
                }
                return leftSize + 1 + rankRB(node->rightCh, key);
            }

    public:
        RBTree() {
            NIL = new RBTNode(0);
            NIL->color = BLACK;
            NIL->size = 0;
            root = NIL;
        }

        void insert(int key) {
            RBTNode* z = new RBTNode(key);
            RBTNode* y = NIL;
            RBTNode* x = root;
            while (x != NIL) {
                y = x;
                x->size++;
                if (z->key < x->key) x = x->leftCh;
                else x = x->rightCh;
            }
            z->parent = y;
            if (y == NIL) root = z;
            else if (z->key < y->key) y->leftCh = z;
            else y->rightCh = z;
            z->leftCh = NIL;
            z->rightCh = NIL;
            z->color = RED;
            insertRB(z);
        }

        bool search(int key) const {
            RBTNode* x = root;
            while (x != NIL) {
                if (key == x->key) return true;
                if (key < x->key) x = x->leftCh;
                else x = x->rightCh;
            }
            return false;
        }

        void remove(int key) {
            RBTNode* z = root;
            while (z != NIL) {
                if (key == z->key) break;
                if (key < z->key) z = z->leftCh;
                else z = z->rightCh;
            }
            if (z == NIL) return;  // Key not found

            RBTNode* y = z;
            RBTNode* x;
            Color yOriginalColor = y->color;
            if (z->leftCh == NIL) {
                x = z->rightCh;
                transplant(z, z->rightCh);
            } else if (z->rightCh == NIL) {
                x = z->leftCh;
                transplant(z, z->leftCh);
            } else {
                y = mini(z->rightCh);
                yOriginalColor = y->color;
                x = y->rightCh;
                if (y->parent == z) x->parent = y;
                else {
                    transplant(y, y->rightCh);
                    y->rightCh = z->rightCh;
                    y->rightCh->parent = y;
                }
                transplant(z, y);
                y->leftCh = z->leftCh;
                y->leftCh->parent = y;
                y->color = z->color;
            }
            delete z;
            if (yOriginalColor == BLACK) deleteFixup(x);

            // Update sizes
            RBTNode* node = x;
            while (node != NIL) {
                node->size = node->leftCh->size + node->rightCh->size + 1;
                node = node->parent;
            }
        }

        void inorderTraversal() const {
            inorderTraverse(root);
        }

        int findmini() const {
            if (root == NIL) throw std::runtime_error("Tree is empty");
            return mini(root)->key;
        }

        int findmaxi() const {
            if (root == NIL) throw std::runtime_error("Tree is empty");
            return maxi(root)->key;
        }

        int select(int k) const {
            if (k < 1 || k > root->size) throw std::out_of_range("Invalid k value");
            return selectRB(root, k-1)->key;
        }

        int rank(int key) const {
            return rankRB(root, key)+1;
        }

        int findPredecessor(int key) const {
            RBTNode* x = root;
            RBTNode* pred = NIL;
            while (x != NIL) {
                if (key > x->key) {
                    pred = x;
                    x = x->rightCh;
                } else if (key < x->key) {
                    x = x->leftCh;
                } else {
                    if (x->leftCh != NIL) return maxi(x->leftCh)->key;
                    if (pred != NIL) return pred->key;
                    throw std::runtime_error("No predecessor");
                }
            }
            throw runtime_error("Key not found");
        }

        int findSuccessor(int key) const {
            RBTNode* x = root;
            RBTNode* succ = NIL;
            while (x != NIL) {
                if (key < x->key) {
                    succ = x;
                    x = x->leftCh;
                } else if (key > x->key) {
                    x = x->rightCh;
                } else {
                    if (x->rightCh != NIL) return mini(x->rightCh)->key;
                    if (succ != NIL) return succ->key;
                    throw std::runtime_error("No successor");
                }
            }
            throw runtime_error("Key not found");
        }
    };

int main() {
    RBTree bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(17);

    cout << "Inorder traversal: ";
    bst.inorderTraversal();
    cout << endl;

    cout << "Minimum: " << bst.findmini() << endl;
    cout << "Maximum: " << bst.findmaxi() << endl;

    cout << "Select(2): " << bst.select(2) << endl;
    cout << "Rank(15): " << bst.rank(15) << endl;

    cout << "Predecessor(12): " << bst.findPredecessor(12) << endl;
    cout << "Successor(12): " << bst.findSuccessor(12) << endl;

    return 0;
}