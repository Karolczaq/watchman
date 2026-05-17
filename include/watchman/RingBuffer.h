//
// Created by Karol Krasoń on 17/05/2026.
//

#ifndef WATCHMAN_RINGBUFFER_H
#define WATCHMAN_RINGBUFFER_H
#include <cstddef>
#include <iterator>

template <typename T>
class RingBuffer {
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
    std::size_t head_;
public:
    class iterator {
        const RingBuffer* buf_;
        std::size_t pos_;
        public:
        iterator(const RingBuffer* buf, std::size_t pos)
              : buf_(buf), pos_(pos) {}

        const T& operator*() const {
            std::size_t start =
                (buf_->head_ + buf_->capacity_ - buf_->size_) % buf_->capacity_;
            return buf_->data_[(start + pos_) % buf_->capacity_];
        }

        iterator& operator++() { ++pos_; return *this; }

        bool operator!=(const iterator& other) const {
            return pos_ != other.pos_;
        }
    };

    iterator begin() const { return iterator(this, 0); }
    iterator end()   const { return iterator(this, size_); }


    explicit RingBuffer(std::size_t capacity);
    ~RingBuffer();
    RingBuffer(const RingBuffer& other);
    RingBuffer(RingBuffer&& other) noexcept;

    RingBuffer& operator=(const RingBuffer& other);
    RingBuffer& operator=(RingBuffer&& other) noexcept;

    void push(const T& value);

    std::size_t size() const {return  size_;};
    std::size_t capacity() const { return capacity_;};

};

template<typename T>
RingBuffer<T>::RingBuffer(std::size_t capacity): data_(new T[capacity]), head_(0), size_(0), capacity_(capacity) {};

template<typename T>
RingBuffer<T>::~RingBuffer() {
    delete[] data_;
}

template<typename T>
void RingBuffer<T>::push(const T &value) {
    data_[head_] = value;
    head_= (head_+1)%capacity_;
    if (size_ < capacity_) {
        size_++;
    }
}

template<typename T>
RingBuffer<T>::RingBuffer(const RingBuffer &other)
     : data_(new T[other.capacity_]),
       size_(other.size_),
       capacity_(other.capacity_),
       head_(other.head_) {
    for (size_t i = 0; i < size_; i++)
        data_[i] = other.data_[i];
}

template<typename T>
RingBuffer<T>::RingBuffer(RingBuffer &&other) noexcept{
    head_ = other.head_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
    other.capacity_ =0;
    other.size_=0;
    other.data_=nullptr;
    other.head_ = 0;
}

template<typename T>
RingBuffer<T>& RingBuffer<T>::operator=(const RingBuffer &other) {
    if (this == &other) return *this;
    delete[] data_;
    head_ = other.head_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
    }
    return *this;
}

template<typename T>
RingBuffer<T>& RingBuffer<T>::operator=(RingBuffer &&other)noexcept {
    if (this == &other) return *this;
    delete[] data_;
    head_ = other.head_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
    other.capacity_ =0;
    other.size_=0;
    other.data_=nullptr;
    other.head_ = 0;
    return *this;
}
#endif //WATCHMAN_RINGBUFFER_H