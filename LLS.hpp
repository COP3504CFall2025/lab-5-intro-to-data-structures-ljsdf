#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template<typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLS() : list() {
    };

    // Insertion
    void push(const T &item) override {
        list.AddTail(item);
    };

    // Deletion
    T pop() override {
        if (list.getCount() == 0) throw std::runtime_error("empty");

        T item{list.getTail()->data};
        list.RemoveTail();
        return item;
    };

    // Access
    T peek() const override {
        if (list.getCount() == 0) throw std::runtime_error("empty");
        return list.getTail()->data;
    };

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };
};
