#ifndef BOUNDED_LIST_WRAPPER_MIPS_SIMULATOR
#define BOUNDED_LIST_WRAPPER_MIPS_SIMULATOR

#include "ListWrapper.h"
#include <vector>
#include "../visual_class_macros.h"

using std::vector;

template<class T>
Class BoundedListWrapepr : public ListWrapper<T>{
private:
    const int CAPACITY;
public:
    BoundedListWrapepr(int capacity = 0) : ListWrapper<T>(), CAPACITY(capacity) {
        
    }

    BoundedListWrapepr<T>(const BoundedListWrapepr<T> &wrapper) : ListWrapper<T>(wrapper), CAPACITY(wrapper.CAPACITY) {

    }

    BoundedListWrapepr<T>(BoundedListWrapepr<T> &&wrapper) noexcept : ListWrapper<T>(wrapper), CAPACITY(wrapper.CAPACITY) {
        
    }

    void pushBack(const T &item) override
    {
        if (this->getSize() == CAPACITY)
            throw std::length_error("Size of bounded list exceeds capacity");
        ListWrapper<T>::pushBack(item);
    }

    void pushFront(const T &item) override
    {
        if (this->getSize() == CAPACITY)
            throw std::length_error("Size of bounded list exceeds capacity");
        ListWrapper<T>::pushFront(item);
    }
};

#endif