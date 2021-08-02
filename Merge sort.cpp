template <typename T>
void _merge(T* arr, int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;

    T* L = new T[left_size];
    T* R = new T[right_size];

    for (int i = 0; i < left_size; ++i)
        L[i] = arr[left + i];

    for (int j = 0; j < right_size; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int m = left;

    for (; i < left_size && j < right_size; ++m) {
        if (L[i] <= R[j])
            arr[m] = L[i++];
        else
            arr[m] = R[j++];
    }

    for (; i < left_size; ++i, ++m)
        arr[m] = L[i];

    for (; j < right_size; ++j, ++m)
        arr[m] = R[j];

    delete [] L;
    delete [] R;
}

template <typename T>
void mergeSort(T* arr, int begin, int end) {
    if (begin >= end) {
        return;
    }

    int mid = (begin + end) / 2;

    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    _merge(arr, begin, mid, end);
}
