//for random - vector, deque
template <typename Iter>
std::size_t m_distance(Iter start, Iter end, std::random_access_iterator_tag)
{
	return end - start;
}

//for forward & bidirectional & input-output
template <typename Iter>
std::size_t m_distance(Iter start, Iter end, std::input_iterator_tag)
{
	std::size_t length = 0;
	while(start != end) {
		++length;
		++start;
	}

	return length;
}

template <typename Iter>
std::size_t it_distance(Iter start, Iter end)
{	
	return m_distance(start, end, typename std::iterator_traits<Iter>::iterator_category());
}
