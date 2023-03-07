#ifndef _BOUNDED_LIST_WRAPPER_MIPS_SIMULATOR_
#define _BOUNDED_LIST_WRAPPER_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "WrapperClasses/ListWrapper.h"

#include <vector>

using std::vector;

template<class T>
Class BoundedListWrapper : public ListWrapper<T>{
private:
    const int capacity;
public:
    BoundedListWrapper(int capacity = 0) : ListWrapper(), capacity(capacity) {
        
    }

    BoundedListWrapper(const BoundedListWrapper &wrapper) : ListWrapper(wrapper), capacity(wrapper.capacity) {

    }

    BoundedListWrapper(BoundedListWrapper &&wrapper) noexcept : ListWrapper(std::move(wrapper)), capacity(wrapper.capacity) {
        
    }

    void pushBack(const T &item) override {
        if (this->getSize() == capacity)
            throw std::length_error("Size of bounded list exceeds capacity");
        ListWrapper::pushBack(item);
    }

    void pushFront(const T &item) override {
        if (this->getSize() == capacity)
            throw std::length_error("Size of bounded list exceeds capacity");
        ListWrapper::pushFront(item);
    }

    virtual T& operator[] (int id) override {
        while (this->getSize() <= id) {
            this->pushBack(0);
        }
        return ListWrapper::operator[](id);
    }
};

#endif