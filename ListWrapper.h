#ifndef LIST_WRAPPER_H
#define LIST_WRAPPER_H

#include <queue>
#include <iterator>
#include <iostream>

template<class T>
Class ListWrapper
{
private:
    std::deque<T> list;
public:
    void pushBack(T item)
    {
        list.push_back(item);
    }

    void pushFront(T item)
    {
        list.push_front(item);
    }

    T getBack()
    {
        return list.back(); 
    }

    T getFront()
    {
        return list.front();
    }

    void popBack()
    {
        list.pop_back();
    }

    void popFront()
    {
        list.pop_front();
    }

    int getSize()
    {
        return list.size();
    }

    bool isEmpty()
    {
        return list.empty();
    }

    ListWrapper() : list(std::deque<T>{})
    {
        
    }

    ListWrapper<T>(const ListWrapper<T> &wrapper) : list(std::deque<T>(wrapper.list))
    {
        std::cout << "Copy constructor";
    }

    //don't know how the fuck this is not called while another move constructor called
    ListWrapper<T>(ListWrapper<T> &&wrapper) noexcept : list(wrapper.list) 
    {
        
    }

    auto cbegin() const
    {
        return begin();
    }

    auto cend() const
    {
        return end();
    }

    auto begin()
    {
        return list.begin();
    }

    auto end()
    {
        return list.end();
    }

    T& operator[] (int id)
    {
        return list.at(id);
    }
};


#endif