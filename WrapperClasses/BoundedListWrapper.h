#ifndef _BOUNDED_LIST_WRAPPER_MIPS_SIMULATOR_
#define _BOUNDED_LIST_WRAPPER_MIPS_SIMULATOR_

#include "ListWrapper.h"
#include <vector>
#include "../visual_class_macros.h"

using std::vector;

template<class T>
Class BoundedListWrapper : public ListWrapper<T>{
private:
    const int capacity;
public:
    BoundedListWrapper(int capacity = 0) : ListWrapper<T>(), capacity(capacity) {
        
    }

    BoundedListWrapper<T>(const BoundedListWrapper<T> &wrapper) : ListWrapper<T>(wrapper), capacity(wrapper.capacity) {

    }

    BoundedListWrapper<T>(BoundedListWrapper<T> &&wrapper) noexcept : ListWrapper<T>(std::move(wrapper)), capacity(wrapper.capacity) {
        
    }

    void pushBack(const T &item) override {
        if (this->getSize() == capacity)
            throw std::length_error("Size of bounded list exceeds capacity");
        ListWrapper<T>::pushBack(item);
    }

    void pushFront(const T &item) override {
        if (this->getSize() == capacity)
            throw std::length_error("Size of bounded list exceeds capacity");
        ListWrapper<T>::pushFront(item);
    }

    virtual T& operator[] (int id) override {
        while (this->getSize() <= id) {
            this->pushBack(0);
        }
        return ListWrapper<T>::operator[](id);
    }
};

#endif