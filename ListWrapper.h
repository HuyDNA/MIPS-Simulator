#ifndef LIST_WRAPPER_MIPS_SIMULATOR
#define LIST_WRAPPER_MIPS_SIMULATOR

#include <queue>

using std::deque;

template<class T>
Class ListWrapper {
private:
    deque<T> list;
public:
    void pushBack(const T& item) {
        list.push_back(item);
    }

    void pushFront(const T& item) {
        list.push_front(item);
    }

    void popBack() {
        list.pop_back();
    }

    void popFront() {
        list.pop_front();
    }

    int getSize() const {
        return list.size();
    }

    bool empty() const {
        return list.empty();
    }

    ListWrapper() : list(deque<T>{}) {
        
    }

    ListWrapper<T>(const ListWrapper<T> &wrapper) : list(deque<T>(wrapper.list)) {

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