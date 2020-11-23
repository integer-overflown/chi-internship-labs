#pragma once
#include <cstddef>

template<typename T, size_t N>
class List
{
    T array[N];
    size_t _size {0};
public:
    typedef const T& reference;

    List() = default;
    [[nodiscard]] size_t size() const;
    reference operator[](size_t index);
    void operator+=(reference element);
};

template<typename T, size_t N>
size_t List<T, N>::size() const {
    return _size;
}

template<typename T, size_t N>
typename List<T, N>::reference List<T, N>::operator[](size_t index) {
    return array[index];
}

template<typename T, size_t N>
void List<T, N>::operator+=(reference element) {
    if (_size < N) array[_size++] = element;
}