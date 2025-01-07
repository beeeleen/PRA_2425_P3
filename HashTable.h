#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// Representa una entrada en la tabla hash
template <typename V>
struct TableEntry {
    std::string key;
    V value;
};

// Lista enlazada básica usando `std::vector` para simplicidad
template <typename T>
class ListLinked {
private:
    std::vector<T> list;

public:
    void push_back(const T& value) {
        list.push_back(value);
    }

    typename std::vector<T>::iterator begin() {
        return list.begin();
    }

    typename std::vector<T>::iterator end() {
        return list.end();
    }

    void erase(typename std::vector<T>::iterator it) {
        list.erase(it);
    }

    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& l) {
        for (const auto& item : l.list) {
            out << "{key: " << item.key << ", value: " << item.value << "} ";
        }
        return out;
    }
};

// Clase HashTable
template <typename V>
class HashTable {
private:
    int max; // Capacidad máxima
    int n;   // Número de entradas
    ListLinked<TableEntry<V>>* table; // Array de listas enlazadas

    // Función hash simple
    int h(const std::string& key) const {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % max;
        }
        return hash;
    }

public:
    // Constructor
    HashTable(int max) : max(max), n(0) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Capacidad
    int capacity() const {
        return max;
    }

    // Número de entradas
    int entries() const {
        return n;
    }

    // Insertar una clave-valor
    void insert(const std::string& key, const V& value) {
        int index = h(key);
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                throw std::runtime_error("Key already exists: " + key);
            }
        }
        table[index].push_back({key, value});
        n++;
    }

    // Buscar un valor por clave
    V search(const std::string& key) const {
        int index = h(key);
        for (const auto& entry : table[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::runtime_error("Key not found: " + key);
    }

    // Eliminar una clave
    bool remove(const std::string& key) {
        int index = h(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                n--;
                return true;
            }
        }
        throw std::runtime_error("Key not found: " + key);
    }

    // Operador de índice para acceder a valores
    V operator[](const std::string& key) const {
        return search(key);
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
        out << "HashTable [entries: " << ht.n << ", capacity: " << ht.max << "]\n";
        for (int i = 0; i < ht.max; ++i) {
            out << "================\nCubeta " << i << " ==\n";
            out << "List => " << ht.table[i] << "\n";
        }
        return out;
    }
};

#endif // HASHTABLE_H

