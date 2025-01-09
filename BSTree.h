#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    BSNode<T>* root;
    int nelem;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (!n) {
            throw std::runtime_error("Elemento no encontrado");
        }
        if (e == n->elem) {
            return n;
        } else if (e < n->elem) {
            return search(n->left, e);
        } else {
            return search(n->right, e);
        }
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (!n) {
            ++nelem;
            return new BSNode<T>(e);
        }
        if (e == n->elem) {
            throw std::runtime_error("Elemento duplicado");
        } else if (e < n->elem) {
            n->left = insert(n->left, e);
        } else {
            n->right = insert(n->right, e);
        }
        return n;
    }

    void print_inorder(std::ostream& out, BSNode<T>* n) const {
        if (!n) return;
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (!n) {
            throw std::runtime_error("Elemento no encontrado");
        }
        if (e < n->elem) {
            n->left = remove(n->left, e);
        } else if (e > n->elem) {
            n->right = remove(n->right, e);
        } else {
            if (!n->left) {
                BSNode<T>* right = n->right;
                delete n;
                --nelem;
                return right;
            } else if (!n->right) {
                BSNode<T>* left = n->left;
                delete n;
                --nelem;
                return left;
            } else {
                T maxVal = max(n->left);
                n->elem = maxVal;
                n->left = remove_max(n->left);
            }
        }
        return n;
    }

    T max(BSNode<T>* n) const {
        while (n->right) {
            n = n->right;
        }
        return n->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (!n->right) {
            BSNode<T>* left = n->left;
            delete n;
            return left;
        }
        n->right = remove_max(n->right);
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (!n) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    BSTree() : root(nullptr), nelem(0) {}

    ~BSTree() {
        delete_cascade(root);
    }

    int size() const {
        return nelem;
    }

    T search(T e) const {
        return search(root, e)->elem;
    }

    void insert(T e) {
        root = insert(root, e);
    }

    void remove(T e) {
        root = remove(root, e);
    }

    T operator[](T e) const {
        return search(e);
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif 

