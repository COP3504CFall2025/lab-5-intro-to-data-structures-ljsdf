#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {

    LinkedList<T> list;

public:
    // Constructor
    LLDQ() : list() {};

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    };
    void pushBack(const T& item) override {
        list.addTail(item);
    };

    // Core Removal Operations
    T popFront() override {
        T item{list.head->data};
        list.removeHead();
        return item;
    };
    T popBack() override {
        T item{list.tail->data};
        list.removeTail();
        return item;
    };

    // Element Accessors
    const T& front() const override {
        return list.tail->data;
    };
    const T& back() const override {
        return list.tail->data;
    };

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };
};






