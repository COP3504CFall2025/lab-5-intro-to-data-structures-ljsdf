#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T> {
    T *data_;
    size_t capacity_;
    size_t size_;

    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ(): data_(new T[1]), capacity_(1), size_(0) {
    };

    explicit ABQ(const size_t capacity): data_(nullptr), capacity_(capacity), size_(0) {
        if (capacity_ == 0) capacity_ = 1;
        data_ = new T[capacity_];
    };

    ABQ(const ABQ &other): // copy
        data_(new T[other.capacity_]),
        capacity_(other.capacity_),
        size_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    };

    ABQ &operator=(const ABQ &other) {
        if (this == &other) return *this;
        delete[] data_;
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    };

    ABQ(ABQ &&other) noexcept : // move
        data_(other.data_),
        capacity_(other.capacity_),
        size_(other.size_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    };

    ABQ &operator=(ABQ &&other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        return *this;
    };

    ~ABQ() noexcept override {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
    };

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return size_;
    };

    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    };

    [[nodiscard]] T *getData() const noexcept {
        return data_;
    };

    // Insertion
    void enqueue(const T &data) override {
        if (size_ == capacity_) {
            T *new_data = new T[capacity_ * scale_factor_];
            for (std::size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = capacity_ * scale_factor_;
        }
        data_[size_] = data;
        size_++;
    };

    // Access
    T peek() const override {
        if (size_ == 0) throw std::runtime_error("empty");

        return data_[0];
    };

    // Deletion
    T dequeue() override {
        // doing it backwards
        if (size_ == 0) {
            throw std::runtime_error("empty");
        }
        if (size_ > 0 && size_ == capacity_ / (scale_factor_ * 2)) {
            size_t new_capacity = capacity_ / scale_factor_;
            if (new_capacity == 0) new_capacity = 1;
            T *new_data = new T[new_capacity];
            for (std::size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        T item = data_[0];
        for (size_t i = 0; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        size_--;
        return item;
    };
};
