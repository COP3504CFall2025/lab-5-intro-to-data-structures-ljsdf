#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

// copy loop
// for (std::size_t i = 0; i < size_; ++i) {
//     std::size_t id = (front_ + i) % capacity_; // loop back
//     data_[id] = other.data_[id];
// }

template <typename T>
class ABDQ : public DequeInterface<T> {
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : data_(new T[1]), capacity_(1),size_(0),front_(0),back_(0) {};
    explicit ABDQ(std::size_t capacity) :data_(nullptr), capacity_(capacity),size_(0),front_(0),back_(0) {
        if (capacity_ == 0) capacity_ = 1;
        data_ = new T[capacity_];
    };
    ABDQ(const ABDQ& other): // copy
      data_(new T[other.capacity_]),
      capacity_(other.capacity_),
      size_(other.size_),
      front_(other.front_),
      back_(other.back_) {
        for (std::size_t i = 0; i < size_; ++i) {
            std::size_t id = (front_ + i) % capacity_; // loop back
            data_[id] = other.data_[id];
        }
    };
    ABDQ(ABDQ&& other) noexcept:// move
      data_(other.data_),
      capacity_(other.capacity_),
      size_(other.size_),
      front_(other.front_),
      back_(other.back_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    };
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;
        delete[] data_;
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        for (std::size_t i = 0; i < size_; ++i) {
            std::size_t id = (front_ + i) % capacity_; // loop back
            data_[id] = other.data_[id];
        }
        return *this;
    };
    ABDQ& operator=(ABDQ&& other) noexcept{
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    };
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    };

    // Insertion
    void pushFront(const T& item) override{
        if (size_ == capacity_) {
            T* new_data = new T[capacity_ * SCALE_FACTOR];
            for (std::size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = capacity_ * SCALE_FACTOR;
            front_ = 0;
            back_ = size_;
        }
        //         2 -1 = 1  1 + 4 % 4 = 1
        //         0 - 1 = -1   -1 + 4 = 3
        front_ = (front_ - 1 + capacity_) % capacity_; // loop around capacity if negative
        data_[front_] = item;
        size_++;
    };
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            T* new_data = new T[capacity_ * SCALE_FACTOR];
            for (std::size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = capacity_ * SCALE_FACTOR;
            front_ = 0;
            back_ = size_;
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_; // never be negative
        size_++;
    };

    // Deletion
    T popFront() override {
        if (size_ == 0) throw std::runtime_error("empty");

        T item = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        return item;
    };
    T popBack() override {
        if (size_ == 0) throw std::runtime_error("empty");

        back_ = (back_ + capacity_ - 1) % capacity_;
        size_--;
        return data_[back_];
    };

    // Access
    const T& front() const override {
        if (size_ == 0) throw std::runtime_error("empty");

        return data_[front_];
    };
    const T& back() const override {
        if (size_ == 0) throw std::runtime_error("empty");

        return data_[(back_ + capacity_ - 1) % capacity_];
    };

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    };

};
