#ifndef _TABLE_WRAPPER_MIPS_SIMULATOR_
#define _TABLE_WRAPPER_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include <map>
#include <stdexcept>

using std::map;

template<class K, class T>
Class TableWrapper {
private:
    map<K,T> table;
public:
    void set(const K &key, const T &value) {
        table[key] = value;
    }

    const T& get(const K &key) const {
        return table.at(key);
    }

    T& get(const K &key) {
        return table.at(key);
    }

    T& operator[](const K &key) {
        return table[key];
    }

    const T& operator[](const K &key) const {
        return table[key];
    }

    auto cbegin() const {
        return table.cbegin();
    }

    auto cend() const {
        return table.cend();
    }

    const auto begin() const {
        return table.begin();
    }

    const auto end() const {
        return table.end();
    }
    
    auto begin() {
        return table.begin();
    }

    auto end() {
        return table.end();
    }

    TableWrapper() : table(map<K,T>()) {

    }

    TableWrapper(const TableWrapper &tableWrapper) : table(tableWrapper.table) {

    }

    TableWrapper(TableWrapper &&tableWrapper) : table(std::move(tableWrapper.table)) {

    }

    TableWrapper& operator=(const TableWrapper &tableWrapper) = delete;
    TableWrapper& operator=(TableWrapper &&tableWrapper) = delete;

    void erase(const K& key) {
        table.erase(key);
    }

    int getSize() const {
        return table.size();
    }

    bool empty() const {
        return table.empty();
    }

};

#endif