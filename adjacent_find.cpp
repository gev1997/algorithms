template <typename Iter, typename Pred>
Iter adjacent_find(Iter start, Iter end, Pred func) {
    if (start == end)
        return start;

    while (std::next(start) != end) {
        if (func(*start, *std::next(start))) {
            return start;
        }
        
        ++start;
    }
    
    return end;
}
