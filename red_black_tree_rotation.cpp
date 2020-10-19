
/*
INSTRUCTIONS
In this assignment, it is required that you fill out areas under comments labeled as "TODO" appropriately based on the accompanying directions.
You are also required to follow any directions accompanying comments such as "NOTE".
You can add/modify code anywhere, with the exception of the provided "main" (which we will use for testing).
You can use the constants RED and BLACK, instead of the ints 0 and 1, when appropriate.
*/

#include <iostream>
#include <assert.h>
#include <math.h> // for asserting height
#include <queue>

using namespace std;

#define RED 0
#define BLACK 1

template <class T>
class RBT;

// swapColor swaps the color from red to black and vice versa
int swapColor(int c) {
    return (c==0)?1:0;
}

template <class T>
class RBTNode {
    RBTNode<T> *parent, *left, *right;
    T data;
    int color;

public:
    RBTNode(T data)
            : data(data),
              color(RED),
              parent(nullptr),
              left(nullptr),
              right(nullptr) {}
    friend class RBT<T>;
    void prettyPrint(int indent) const;

    template <class T1>
    friend void swapColor(RBTNode<T1> *);
    template <class T1>
    friend int getColor(RBTNode<T1> *);
    template<class T1>
    friend void setColor(RBTNode<T1> *, bool);

    int height() const;
};

template <class T>
int RBTNode<T>::height() const {
    int left_h = 0;
    if (left != nullptr) {
        left_h = left->height();
    }
    int right_h = 0;
    if (right != nullptr) {
        right_h = right->height();
    }
    return 1 + max(left_h, right_h);
}

template <class T>
void RBTNode<T>::prettyPrint(int indent) const {
    if (right != nullptr) {
        right->prettyPrint(indent + 1);
    }
    int margin = indent * 2;
    for (int i = 0; i < margin; ++i) {
        cout << '\t' << '\t';
    }
    cout << "DATA: " << data << endl;
    for (int i = 0; i < margin; ++i) {
        cout << '\t' << '\t';
    }
    cout << "COLOR: " << (color == RED ? "RED" : "BLACK") << endl;
    if (left != nullptr) {
        left->prettyPrint(indent + 1);
    }
}

template <class T>
void swapColor(RBTNode<T> *node) {
    if (node != nullptr) {
        node->color = swapColor(node->color);
    }
}

// getColor handles null nodes
template <class T>
int getColor(RBTNode<T> *node) {
    if (node != nullptr) {
        return node->color;
    }
    return BLACK;
}

template <class T>
void setColor(RBTNode<T> *node, bool color) {
    if (node != nullptr) {
        node->color = color;
    }
}

template <class T>
class RBT {
    RBTNode<T> *root;
    void singleRotateRight(RBTNode<T> *&point);
    void singleRotateLeft(RBTNode<T> *&point);

public:
    RBT() : root(nullptr) {}

    void insert(const T &);
    void insert(const T &, RBTNode<T> *&point, RBTNode<T> *parent);
    void fixInsert(RBTNode<T> *point);
    void prettyPrint() const { root->prettyPrint(0); }

    int height() const { return root->height(); }
};

template <class T>
void RBT<T>::singleRotateRight(RBTNode<T> *&point) {
    RBTNode<T> *left_child = point->left;
    point->left = left_child->right;
    if (point->left)
        point->left->parent = point;
    left_child->parent = point->parent;
    if (!point->parent)
        root = left_child;
    else if (point == point->parent->left)
        point->parent->left = left_child;
    else
        point->parent->right = left_child;
    left_child->right = point;
    point->parent = left_child;
}

template <class T>
void RBT<T>::singleRotateLeft(RBTNode<T> *&point) {
    RBTNode<T> *right_child = point->right;
    point->right = right_child->left;
    if (point->right)
        point->right->parent = point;
    right_child->parent = point->parent;
    if (!point->parent)
        root = right_child;
    else if (point == point->parent->left)
        point->parent->left = right_child;
    else
        point->parent->right = right_child;
    right_child->left = point;
    point->parent = right_child;
}

template <class T>
void RBT<T>::fixInsert(RBTNode<T> *point) {
    RBTNode<T> *parent = nullptr;
    RBTNode<T> *grandparent = nullptr;
    while (point != root && getColor(point) == RED && getColor(point->parent) == RED) {
        parent = point->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            if (getColor(grandparent->right) == RED) {
                swapColor(grandparent->right);
                swapColor(parent);
                setColor(grandparent, RED);
                point = grandparent;
            } else {
                if (point == parent->right) {
                    singleRotateLeft(parent);
                    point = parent;
                    parent = point->parent;
                }
                singleRotateRight(grandparent);
                swapColor(parent);
                swapColor(grandparent);
                point = parent;
            }
        }
        else {
            if (getColor(grandparent->left) == RED) {
                swapColor(grandparent->left);
                swapColor(parent);
                setColor(grandparent, RED);
                point = grandparent;
            } else {
                if (point == parent->left) {
                    singleRotateRight(parent);
                    point = parent;
                    parent = point->parent;
                }
                singleRotateLeft(grandparent);
                swapColor(parent);
                swapColor(grandparent);
                point = parent;
            }
        }
    }
    setColor(root, BLACK);
}

template <class T>
void RBT<T>::insert(const T &toInsert, RBTNode<T> *&point, RBTNode<T> *parent) {
    if (point == nullptr) {               // leaf location is found so insert node
        point = new RBTNode<T>(toInsert); // modifies the pointer itself since *point
        // is passed by reference
        point->parent = parent;
        fixInsert(point);
    }
    else if (toInsert < point->data) { // recurse down the tree to left to find correct leaf location
        insert(toInsert, point->left, point);
    } else { // recurse down the tree to right to find correct leaf location
        insert(toInsert, point->right, point);
    }
}

template <class T>
void RBT<T>::insert(const T &toInsert) {
    insert(toInsert, root, nullptr);
}

// NOTE: DO NOT MODIFY THE MAIN FUNCTION BELOW
int main() {
    RBT<int> b;
    int count = 10;
    for (int i = 0; i < count; i++) {
        b.insert(i);
    }

    b.prettyPrint();
    /* EXPECTED OUTPUT:
                                                                    Data: 9
                                                                    COLOR: RED
                                                    Data: 8
                                                    COLOR: BLACK
                                    Data: 7
                                    COLOR: RED
                                                    Data: 6
                                                    COLOR: BLACK
                    Data: 5
                    COLOR: BLACK
                                    Data: 4
                                    COLOR: BLACK
    Data: 3
    COLOR: BLACK
                                    Data: 2
                                    COLOR: BLACK
                    Data: 1
                    COLOR: BLACK
                                    Data: 0
                                    COLOR: BLACK
    */

    // TEST
    // the below tests the validity of the height of the RBT
    // if the assertion fails, then your tree does not properly self-balance
    int height = b.height();
    assert(height <= 2 * log2(count));
}
