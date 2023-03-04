#ifndef TABLE_WRAPPER_MIPS_SIMULATOR
#define TABLE_WRAPPER_MIPS_SIMULATOR

#include <map>

using std::map;

template<class K, class T>
Class TableWrapper {
private:
    map<K,T> table;
public:
    void set(const K &key, const T &value) {
        table.at(key) = value;
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

    auto cbegin() {
        return table.cbegin();
    }

    auto cend() {
        return table.cend();
    }

    auto begin() {
        return table.begin();
    }

    auto end() {
        return table.end();
    }

    TableWrapper() : table(map<K,T>()) {

    }

    TableWrapper(const TableWrapper &tableWrapper) : table(map<K,T>(tableWrapper.table)) {

    }

    TableWrapper(TableWrapper &&tableWrapper) : table(tableWrapper.table) {

    }

    int count() const {
        return table.count();
    }

    void erase(const K& key) {
        table.erase(key);
    }

    int size() const {
        return table.size();
    }

    bool empty() const {
        return table.empty();
    }

};

#endif