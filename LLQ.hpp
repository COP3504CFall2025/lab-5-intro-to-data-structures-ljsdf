#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() : list() {};

    // Insertion
    void enqueue(const T& item) override {
        list.addHead(item);
    };

    // Deletion
    T dequeue() override {
        T item{list.head->data};
        list.removeHead();
        return item;
    };

    // Access
    T peek() const override{
        return list.tail->data;
    };

    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    };

};