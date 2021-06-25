#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class heapSort {
public:
    template <typename Iter>
    heapSort(Iter begin, Iter end) : _data(begin, end)
                                    , _size{static_cast<unsigned int>(_data.size())}
    {
        _heapSort();
    }

    std::vector<T> data() {
        return _data;
    }

private:
    std::vector<T> _data;
    unsigned int _size;

private:
    void _maxHeapify(int i) {
        int l = 2 * i;
        int r = (2 * i) + 1;
        int largest = 0;

        if (l <= _size && _data[l] > _data[i]) {
            largest = l;
        }
        else {
            largest = i;
        }

        if(r <= _size && _data[r] > _data[largest]) {
            largest = r;
        }
        
        if (largest != i) {
            std::swap(_data[i], _data[largest]);
            _maxHeapify(largest);
        }
    }

    void _buildMaxHeap() {
        for (int i = _size / 2; i >= 0; --i) {
            _maxHeapify(i);
        }
    }

    void _heapSort() {
        _buildMaxHeap();

        for (int i = _size; i >= 1; --i) {
            std::swap(_data[0], _data[i]);
            --_size;

            _maxHeapify(0);
        }
    }
};

#endif //HEAP_SORT_H