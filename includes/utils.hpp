#pragma once

#include <iostream>
#include <cstddef>

namespace ft
{

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, 
           InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, 
           InputIt2 first2, BinaryPredicate p)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!p(*first1, *first2)) {
            return false;
        }
    }
    return true;
}

template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };

template <class T>
struct is_integral {
	static const bool value = false;
};

template <>
struct is_integral<bool> {
	static const bool value = true;
};

template <>
struct is_integral<char> {
	static const bool value = true;
};

template <>
struct is_integral<wchar_t> {
	static const bool value = true;
};

template <>
struct is_integral<signed char> {
	static const bool value = true;
};

template <>
struct is_integral<short int> {
	static const bool value = true;
};

template <>
struct is_integral<int> {
	static const bool value = true;
};

template <>
struct is_integral<long int> {
	static const bool value = true;
};

template <>
struct is_integral<long long int> {
	static const bool value = true;
};

template <>
struct is_integral<unsigned char> {
	static const bool value = true;
};

template <>
struct is_integral<unsigned short int> {
	static const bool value = true;
};

template <>
struct is_integral<unsigned int> {
	static const bool value = true;
};

template <>
struct is_integral<unsigned long int> {
	static const bool value = true;
};

template <>
struct is_integral<unsigned long long int> {
	static const bool value = true;
};

template <typename U>
void swap(U& x, U& y)
{
	U copy = x;
	x = y;
	y = copy;
}

// template <bool is_integral, typename T>
// struct is_integral_res {
// 	typedef T type;
// 	static const bool value = is_integral;
// };

// template <typename>
// struct is_integral_type : public is_integral_res<false, bool> {};

// template <>
// struct is_integral_type<bool> : public is_integral_res<true, bool> {};

// template <>
// struct is_integral_type<char> : public is_integral_res<true, char> {};

// template <>
// struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

// template <>
// struct is_integral_type<short int> : public is_integral_res<true, short int> {};

// template <>
// struct is_integral_type<int> : public is_integral_res<true, int> {};

// template <>
// struct is_integral_type<long int> : public is_integral_res<true, long int> {};

// template <>
// struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

// template <>
// struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

// template <>
// struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

// template <>
// struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

// template <>
// struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};

// template <>
// struct is_integral_type<unsigned long long> : public is_integral_res<true, unsigned long long> {};

// template <typename T>
// struct is_integral : public is_integral_type<T> {};

//validator

// class input_iterator_tag {};
// class output_iterator_tag {};
// class forward_iterator_tag {};
// class bidirectional_iterator_tag {};
// class random_access_iterator_tag {};

// template <bool is_valid, typename T>
// struct valid_iterator_tag_res {typedef T type; const static bool value = is_valid;};

// template <typename T>
// struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> {};

// template <>
// struct is_input_iterator_tagged<ft::random_access_iterator_tag> : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};

// template <>
// struct is_input_iterator_tagged<ft::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};

// template <>
// struct is_input_iterator_tagged<ft::forward_iterator_tag> : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};

// template <>
// struct is_input_iterator_tagged<ft::input_iterator_tag> : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};

// //true if the iterator is tagged
// template <typename T>
// struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> {};

// template <>
// struct is_ft_iterator_tagged<ft::random_access_iterator_tag> : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};

// template <>
// struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};

// template <>
// struct is_ft_iterator_tagged<ft::forward_iterator_tag> : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};

// template <>
// struct is_ft_iterator_tagged<ft::output_iterator_tag> : public valid_iterator_tag_res<true, ft::output_iterator_tag> {};

// template <>
// struct is_ft_iterator_tagged<ft::input_iterator_tag> : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};

// template<class InputItrator>
// typename ft::iterator_traits<InputItrator>::difference_type distance (InputItrator first, InputItrator last)
// {
// 	typename ft::iterator_traits<InputItrator>::difference_type ret = 0;
// 	while (first != last)
// 	{
// 		first++;
// 		ret++;
// 	}
// 	return ret;
// }

}