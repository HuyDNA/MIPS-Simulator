#ifndef LIST_WRAPPER_MIPS_SIMULATOR
#define LIST_WRAPPER_MIPS_SIMULATOR

#include "../visual_class_macros.h"
#include <vector>

using std::vector;

template<class T>
Class ListWrapper {
private:
    vector<T> list;
public:
    void pushBack(const T& item) {
        list.push_back(item);
    }

    void pushFront(const T& item) {
        list.push_back(item);
        for (int i = list.size() - 1; i > 0; --i)
        {
            list[i] = list[i - 1];
        }
        list[0] = item;
    }

    void popBack() {
        list.pop_back();
    }

    void popFront() {
        for (int i = 0; i < list.size() - 1; ++i)
        {
            list[i] = list[i + 1];
        }
        list.pop_back();
    }

    int getSize() const {
        return list.size();
    }

    bool empty() const {
        return list.empty();
    }

    ListWrapper() : list(vector<T>{}) {
        
    }

    ListWrapper<T>(const ListWrapper<T> &wrapper) : list(vector<T>(wrapper.list)) {

    }

    ListWrapper<T>(ListWrapper<T> &&wrapper) noexcept : list(wrapper.list) {
        
    }

    auto cbegin() const {
        return list.cbegin();
    }

    auto cend() const {
        return list.cend();
    }

    auto begin() {
        return list.begin();
    }

    auto end() {
        return list.end();
    }

    const T& operator[] (int id) const {
        return list.at(id);
    }

    T& operator[] (int id) {
        return list.at(id);
    }
};

#endif