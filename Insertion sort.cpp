template <typename T>
void insert_sort(T begin, T end) {
    T start = begin;

    while (begin != end) {
        T temp = begin;

        while ((temp > start) && *(temp - 1) > *(temp)) {
            std::swap(*temp, *(temp - 1));
            --temp;
        }

        ++begin;
    }
}
