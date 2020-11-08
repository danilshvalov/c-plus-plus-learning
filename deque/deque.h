#include <vector>
#include <stdexcept>

#ifndef __DEQUE_H__
#define __DEQUE_H__

/*
    Дублирование кода оправдано константностью времени доступа к элементам
*/

template <typename T>
class Deque {
private:
    std::vector<T> leftSide;
    std::vector<T> rightSide;
    size_t size = 0;
public:
    bool Empty() const {
        return size == 0;
    }
    size_t Size() const {
        return size;
    }
    T& operator[](size_t index) {
        if (index >= leftSide.size()) {
            return rightSide[index - leftSide.size()];
        }
        return leftSide[leftSide.size() - index - 1];
    }
    const T& operator[](size_t index) const {
        if (index >= leftSide.size()) {
            return rightSide[index - leftSide.size()];
        }
        return leftSide[leftSide.size() - index - 1];
    }
    T& At(size_t index) {
        if (index >= size || index < 0) {
            throw std::out_of_range("Out of range");
        }
        return this->operator[](index);
    }
    const T& At(size_t index) const {
        if (index >= size || index < 0) {
            throw std::out_of_range("Out of range");
        }
        return this->operator[](index);
    }
    const T& Front() const {
        if (leftSide.empty()) {
            return rightSide.front();
        }
        return leftSide.back();
    }
    const T& Back() const {
        if (rightSide.empty()) {
            return leftSide.front();
        }
        return rightSide.back();
    }
    T& Front() {
        if (leftSide.empty()) {
            return rightSide.front();
        }
        return leftSide.back();
    }
    T& Back() {
        if (rightSide.empty()) {
            return leftSide.front();
        }
        return rightSide.back();
    }
    void PushFront(T value) {
        leftSide.push_back(std::move(value));
        ++size;
    }
    void PushBack(T value) {
        rightSide.push_back(std::move(value));
        ++size;
    }
};

#endif // __DEQUE_H__