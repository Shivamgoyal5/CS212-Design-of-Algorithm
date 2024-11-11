#include<bits/stdc++.h>
using namespace std;

class NodeBST{
    public:
        int key;
        NodeBST* leftCh;
        NodeBST* rightCh;
        NodeBST* parent;
        int size;

        NodeBST(int k) : key(k), leftCh(nullptr), rightCh(nullptr), parent(nullptr), size(1) {}
    };
class BST {
    private:
        NodeBST* root;

        NodeBST* insertBST(NodeBST* node,int key){
            if(node==nullptr){
                return new NodeBST(key);
            }
            if(key<node->key){
                node->leftCh=insertBST(node->leftCh,key);
                node->leftCh->parent=node;
            }
            else{
                node->rightCh=insertBST(node->rightCh,key);
                node->rightCh->parent=node;
            }
            node->size++;
            return node;
        }

        bool searchBST(NodeBST* node,int key) const{
            if(node == nullptr){return false;}
            if(node->key == key){return true;}
            if(key<node->key){return searchBST(node->leftCh,key);}
            return searchBST(node->rightCh,key);
        }

        NodeBST* deleteBST(NodeBST* node, int key){
            if(node==nullptr){return nullptr;}
            if(key<node->key){
                node->leftCh=deleteBST(node->leftCh,key);
            }
            else if(key>node->key){
                node->rightCh=deleteBST(node->rightCh,key);
            }
            else{
                if(node->leftCh ==nullptr){
                    NodeBST* temp=node->rightCh;
                    delete node;
                    return temp;
                }
                else if(node->rightCh ==nullptr){
                    NodeBST* temp =node->leftCh;
                    delete node;
                    return temp;
                }
                NodeBST* minNode =findMin(node->rightCh);
                node->key=minNode->key;
                node->rightCh=deleteBST(node->rightCh,minNode->key);
                }
                updateSize(node);
                return node;
            }

            void inorderTraverse(NodeBST* node) const {
                if (node == nullptr) return;
                inorderTraverse(node->leftCh);
                cout<<node->key<<" ";
                inorderTraverse(node->rightCh);
            }

            NodeBST* findMin(NodeBST* node) const {
                while (node->leftCh != nullptr) {
                    node = node->leftCh;
                }
                return node;
            }

            NodeBST* findMax(NodeBST* node) const {
                while (node->rightCh != nullptr) {
                    node = node->rightCh;
                }
                return node;
            }

            NodeBST* selectBST(NodeBST* node, int k) const {
                if (node == nullptr) return nullptr;
                int leftSize = (node->leftCh != nullptr) ? node->leftCh->size : 0;
                if (leftSize == k) return node;
                if (leftSize > k) return selectBST(node->leftCh, k);
                return selectBST(node->rightCh, k - leftSize - 1);
            }

            int rankBST(NodeBST* node, int key) const {
                if (node == nullptr) return 0;
                if (key < node->key) return rankBST(node->leftCh, key);
                int leftSize = (node->leftCh != nullptr) ? node->leftCh->size : 0;
                if (key == node->key) return leftSize;
                return leftSize + 1 + rankBST(node->rightCh, key);
            }

            NodeBST* searchNode(NodeBST* node, int key) const {
                if (node == nullptr) return nullptr;
                if (key < node->key) return searchNode(node->leftCh, key);
                if (key > node->key) return searchNode(node->rightCh, key);
                return node;
            }

            void updateSize(NodeBST* node) {
                node->size = 1;
                if (node->leftCh != nullptr) node->size += node->leftCh->size;
                if (node->rightCh != nullptr) node->size += node->rightCh->size;
            }

            public:
                BST() : root(nullptr) {}

                void insert(int key) {
                    root = insertBST(root, key);
                }

                bool search(int key) const {
                    return searchBST(root, key);
                }

                void remove(int key) {
                    root = deleteBST(root, key);
                }

                void inorderTraverse() const {
                    inorderTraverse(root);
                }

                int findMin() const {
                    if (root == nullptr) throw length_error("empty tree");
                    return findMin(root)->key;
                }

                int findMax() const {
                    if (root == nullptr) throw length_error("empty tree");
                    return findMax(root)->key;
                }

                int select(int k) const {
                    if (k < 0 || k >= root->size) throw invalid_argument("out of range");
                    return selectBST(root, k-1)->key;
                }

                int rank(int key) const {
                    return rankBST(root, key)+1;
                }

                int findSuccessor(int key) const {
                    NodeBST* node = searchNode(root, key);
                    if (node == nullptr) throw invalid_argument("key not found");
                    if (node->rightCh != nullptr) return findMin(node->rightCh)->key;
                    NodeBST* parent = node->parent;
                    while (parent != nullptr && node == parent->rightCh) {
                        node = parent;
                        parent = parent->parent;
                    }
                    if (parent == nullptr) throw invalid_argument("successor does not exist");
                    return parent->key;
                }

                int findPredecessor(int key) const {
                    NodeBST* node = searchNode(root, key);
                    if (node == nullptr) throw invalid_argument("key not found");
                    if (node->leftCh != nullptr) return findMax(node->leftCh)->key;
                    NodeBST* parent = node->parent;
                    while (parent != nullptr && node == parent->leftCh) {
                        node = parent;
                        parent = parent->parent;
                    }
                    if (parent == nullptr) throw invalid_argument("predecessor does not exist");
                    return parent->key;
                }


        };

int main() {
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(17);

    cout << "Inorder traversal: ";
    bst.inorderTraverse();
    cout << endl;

    cout << "Minimum: " << bst.findMin() << endl;
    cout << "Maximum: " << bst.findMax() << endl;

    cout << "Select(2): " << bst.select(2) << endl;
    cout << "Rank(15): " << bst.rank(15) << endl;

    cout << "Predecessor(12): " << bst.findPredecessor(12) << endl;
    cout << "Successor(12): " << bst.findSuccessor(12) << endl;

    return 0;
}
    
