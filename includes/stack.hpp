#pragma once

#include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack {
public:
	typedef Container container_type;
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type size_type;
	typedef typename Container::reference reference;
	typedef typename Container::const_reference const_reference;

	explicit stack(const Container& cont = Container()) : c(cont) {}

	virtual ~stack() {}

	stack& operator=(const stack& other) {
		if (this != &other) {
			c = other.c;
		}
		return (*this);
	}

	/*------------element access-------------*/
	reference top() {
		return c.back();
	}

	const_reference top() const {
		return c.back();
	}

	/*------------capacity-------------*/

	bool empty() const {
		return c.empty();
	}

	size_type size() const {
		return c.size();
	}

	/*------------modifiers-------------*/

	void push ( const value_type& value ) {
		c.push_back(value);
	}

	void pop() {
		c.pop_back();
	}

template< class ST, class CT>
friend bool operator==(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs);

template< class ST, class CT>
friend bool operator!=(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs);

template< class ST, class CT>
friend bool operator<(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs);

template< class ST, class CT>
friend bool operator<=(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs);

template< class ST, class CT>
friend bool operator>(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs);

template< class ST, class CT>
friend bool operator>=(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs);

protected:
	Container c;
};

template< class ST, class CT>
bool operator==(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs) {
	return lhs.c == rhs.c;
}

template< class ST, class CT>
bool operator!=(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs) {
	return lhs.c != rhs.c;
}

template< class ST, class CT>
bool operator<(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs) {
	return lhs.c < rhs.c;
}

template< class ST, class CT>
bool operator<=(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs) {
	return lhs.c <= rhs.c;
}

template< class ST, class CT>
bool operator>(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs) {
	return lhs.c > rhs.c;
}

template< class ST, class CT>
bool operator>=(const ft::stack<ST, CT>& lhs, const ft::stack<ST, CT>& rhs) {
	return lhs.c >= rhs.c;
}

}
