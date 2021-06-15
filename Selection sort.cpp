template <typename T>
void select_sort(T begin, T end) {
    while (begin != end) {
        for (T temp = begin + 1; temp != end; ++temp) {
            if (*begin > *temp) {
                std::swap(*begin, *temp);
            }
        }

        ++begin;
    }
}
