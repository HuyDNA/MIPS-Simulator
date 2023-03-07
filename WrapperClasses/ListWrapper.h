#ifndef _LIST_WRAPPER_MIPS_SIMULATOR_
#define _LIST_WRAPPER_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include <vector>

using std::vector;

template<class T>
Class ListWrapper {
private:
    vector<T> list;
public:
    virtual void pushBack(const T& item) {
        list.push_back(item);
    }

    virtual void pushFront(const T& item) {
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

    ListWrapper(const ListWrapper &wrapper) : list(wrapper.list) {

    }

    ListWrapper(ListWrapper &&wrapper) noexcept : list(std::move(wrapper.list)) {
        
    }

    ListWrapper& operator=(const ListWrapper &wrapper) = delete;
    ListWrapper& operator=(ListWrapper<T> &&wrapper) = delete;

    auto cbegin() const {
        return list.cbegin();
    }

    auto cend() const {
        return list.cend();
    }

    const auto begin() const {
        return list.begin();
    }

    const auto end() const {
        return list.end();
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

    virtual T& operator[] (int id) {
        return list.at(id);
    }
};

#endif