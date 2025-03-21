#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    ~BSTreeDict() {
        delete tree;
    }

    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    V search(std::string key) override {
        TableEntry<V> entry(key);
        return tree->search(entry).value;
    }

    V remove(std::string key) override {
        TableEntry<V> entry(key);
        V value = tree->search(entry).value;
        tree->remove(entry);
        return value;
    }

    int entries() const override {
        return tree->size();
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif

