#ifndef BINARYINDEXEDTREE_BIT_HPP
#define BINARYINDEXEDTREE_BIT_HPP

#include <cstddef>
#include <functional>
#include <cassert>

template <typename T>
class BIT {
private:
    T *_data;
    T *_tree;
    std::size_t _size;
    std::function<T(T, T)> _binFunc;

    // Gets index as [1, n] due to binary calculation
    void _update(std::size_t idx, T t) {
        while(idx <= _size) {
            _tree[idx] = _binFunc(_tree[idx], t);
            idx += (idx & (~idx + 1));
        }
    }

public:
    template <typename DataIterator>
    BIT(std::size_t size, std::function<T(T, T)> func, DataIterator dit)
            : _size(size), _binFunc(func), _data(new T[size + 1]()), _tree(new T[size + 1]()) {
        std::copy(dit, dit + size, _data + 1);
        for(std::size_t i = 1; i <= size; i++) {
            _update(i, _data[i]);
        }
    }

    ~BIT() {
        delete[] _data;
        delete[] _tree;
    }

    [[deprecated]]
    void add_element(T const &t) {
        T *new_data = new T[_size + 2];
        std::copy(_data + 1, _data + (++_size), new_data + 1);
        new_data[_size] = t;
        std::swap(_data, new_data);
        delete[] new_data;
        delete[] _tree;
        _tree = new T[_size + 1];
        for(std::size_t i = 1; i <= _size; i++) {
            _update(i, _data[i]);
        }
    }
    [[deprecated]]
    void add_element(T &&t) {
        T *new_data = new T[_size + 2];
        std::copy(_data + 1, _data + (++_size), new_data + 1);
        new_data[_size] = std::move(t);
        std::swap(_data, new_data);
        delete[] new_data;
        delete[] _tree;
        _tree = new T[_size + 1];
        for(std::size_t i = 1; i <= _size; i++) {
            _update(i, _data[i]);
        }
    }

    // Get the computed value in the range [0, idx - 1]
    T get(std::size_t idx) const {
        T ret{};
        idx++;
        while(idx > 0) {
            ret = _binFunc(_tree[idx], ret);
            idx -= (idx & (~idx + 1));
        }
        return ret;
    }

    // Gets index as [0, n - 1]
    void set(std::size_t idx, T t) {
        if(idx >= _size) throw std::runtime_error("Index out of range!");
        _update(idx + 1, t);
    }

    constexpr std::size_t size() const { return _size; }

    void swap(BIT &bit) {
        std::swap(_data, bit._data);
        std::swap(_tree, bit._tree);
        std::swap(_size, bit._size);
        std::swap(_binFunc, bit._binFunc);
    }
};


#endif
