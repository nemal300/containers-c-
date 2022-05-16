#pragma once

#include "utils.hpp"
#include "treeavl.hpp"

namespace ft {

template <class Iterator>
struct iterator_traits {
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T*> {
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
class iterator
{
public:
	typedef Category	iterator_category;
	typedef T 			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference 	reference;
};

template<class T>
class vector_iterator : public iterator<std::random_access_iterator_tag, typename iterator_traits<T>::value_type> {
public:
	typedef T iterator_type;
	typedef typename iterator_traits<T>::difference_type difference_type;
	typedef typename iterator_traits<T>::pointer pointer;
	typedef typename iterator_traits<T>::reference reference;

private:
	iterator_type _ptr;

public:
	vector_iterator() : _ptr(iterator_type()) {}

	vector_iterator(iterator_type ptr) : _ptr(ptr) {}

	template <class Iter>
	vector_iterator(const vector_iterator<Iter>& other) : _ptr(other.base()) {}

	iterator_type base() const {
		return _ptr;
	}

	reference operator*(void) const {
		iterator_type tmp = base();
		return (*tmp);
	}

	vector_iterator operator+(difference_type n) const
	{
		return vector_iterator(base() + n);
	}

	vector_iterator& operator++() {
		++_ptr;
		return (*this);
	}

	vector_iterator operator++(int)
	{
		vector_iterator tmp = *this;
		++_ptr;
		return (tmp);
	}

	vector_iterator& operator+=(difference_type n)
	{
		_ptr += n;
		return *this;
	}

	vector_iterator operator-(difference_type n) const
	{
		return vector_iterator(base() - n);
	}

	vector_iterator& operator--()
	{
		--_ptr;
		return (*this);
	}

	vector_iterator operator--(int)
	{
		vector_iterator ret = *this;

		--_ptr;
		return (ret);
	}

	// vector_iterator& operator-=(int n)
	// {
	// 	_ptr -= n;
	// 	return *this;
	// }

	pointer operator->() const {
		iterator_type tmp = base();
		return &*tmp;
	}

	reference operator[](difference_type n) const
	{
		return (*(*this + n));
	}
};

template <class Iterator>
bool operator==(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!=(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator<=(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
bool operator>(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator>=(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
vector_iterator<Iterator> operator+(typename vector_iterator<Iterator>::difference_type n, const vector_iterator<Iterator> &rev_it)
{
	return vector_iterator<Iterator>(rev_it.base() + n);
}

template <class Iterator>
typename vector_iterator<Iterator>::difference_type operator-(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs)
{
	return lhs.base() - rhs.base();
}

template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator iterator_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer pointer;
	typedef typename ft::iterator_traits<Iterator>::reference reference;

	reverse_iterator() : _ptr(iterator_type()) {}

	reverse_iterator(iterator_type it) : _ptr(it) {}

	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter> &oth) : _ptr(oth.base()) {}

	iterator_type base() const {
		return _ptr;
	}

	reference operator*() const {
		iterator_type tmp = base();
		return *--tmp;
	}

	reverse_iterator operator+(difference_type n) const {
		return reverse_iterator(base() - n);
	}

	reverse_iterator& operator++() {
		--_ptr;
		return *this;
	}

	reverse_iterator operator++(int) {
		reverse_iterator ret = *this;

		--_ptr;
		return ret;
	}

	reverse_iterator& operator+=(difference_type n)
	{
		_ptr = _ptr - n;
		return *this;
	}

	reverse_iterator operator-(difference_type n) const {
		return reverse_iterator(base() + n);
	}

	reverse_iterator& operator--() {
		++_ptr;
		return *this;
	}

	reverse_iterator operator--(int) {
		reverse_iterator ret = *this;

		++_ptr;
		return ret;
	}

	pointer operator->() const {
		iterator_type tmp = base();
		return &*--tmp;
	}

	reference operator[](difference_type n) const{
		return *(*this + n);
	}

	// reverse_iterator& operator-=(difference_type n) {
	// 	_ptr += n;
	// 	return *this;
	// }

	private:
		iterator_type _ptr;
};

template< class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() == rhs.base());
}

template< class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() != rhs.base());
}

template< class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() > rhs.base());
}
template< class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() >= rhs.base());
}

template< class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() < rhs.base());
}

template< class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it) {
	return reverse_iterator<Iterator>(rev_it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
	return rhs.base() - lhs.base();
}

template<typename T>
class TreavlIter : iterator<T, bidirectional_iterator_tag> {
public:
	typedef bidirectional_iterator_tag iterator_category;
	typedef typename ft::iterator_traits<T*>::value_type value_type;
	typedef typename ft::iterator_traits<T*>::pointer pointer;
	typedef typename ft::iterator_traits<T*>::reference reference;
	typedef typename ft::iterator_traits<T*>::difference_type difference_type;
	typedef typename ft::_node<value_type>* node_pointer;
	
	TreavlIter() : _pnode(NULL) {}

	TreavlIter(node_pointer other) : _pnode(other) {}

	TreavlIter(const TreavlIter& other) : _pnode(other._pnode) {}

	TreavlIter& operator=(const TreavlIter& other) {
		if (this != &other) {
			_pnode = other._pnode;
		}
		return *this;
	}

	node_pointer base() const {
		return _pnode;
	}

	reference operator*() const {
		return _pnode->value;
	}

	pointer operator->() const {
		return &(_pnode->value);
	}

	TreavlIter& operator++() {
		if (_pnode->right) {
			_pnode = treap_subtree_min(_pnode->right);
		}
		else {
			node_pointer parent = _pnode->parent;
			while (parent && parent->right == _pnode) {
				_pnode = parent;
				parent = _pnode->parent;
			}
			if (parent) {
				_pnode = parent;
			}
		}
		return *this;
	}

	TreavlIter operator++(int) {
		TreavlIter<T> temp(*this);

		if (_pnode->right) {
			_pnode = treap_subtree_min(_pnode->right);
		}
		else {
			node_pointer parent = _pnode->parent;
			while (parent && parent->right == _pnode) {
				_pnode = parent;
				parent = _pnode->parent;
			}
			if (parent) {
				_pnode = parent;
			}
		}
		return temp;
	}

	TreavlIter& operator--() {
		if (_pnode->left) {
			_pnode = treap_subtree_max(_pnode->left);
		} 
		else {
			node_pointer parent = _pnode->parent;
			while (parent && parent->left == _pnode) {
				_pnode = parent;
				parent = _pnode->parent;
			}
			if (parent) {
				_pnode = parent;
			}
		}
		return *this;
	}

	TreavlIter operator--(int) {
		TreavlIter<T> temp(*this);
		if (_pnode->left) {
			_pnode = treap_subtree_max(_pnode->left);
		} 
		else {
			node_pointer parent = _pnode->parent;
			while (parent && parent->left == _pnode) {
				_pnode = parent;
				parent = _pnode->parent;
			}
			if (parent) {
				_pnode = parent;
			}
		}
		return temp;
	}
private:
	node_pointer treap_subtree_max(node_pointer ptreap) const {
		if (!ptreap->right) {
			return ptreap;
		}
		else {
			return treap_subtree_max(ptreap->right);
		}
	}

	node_pointer treap_subtree_min(node_pointer ptreap) const {
		if (!ptreap->left) {
			return ptreap;
		}
		else {
			return treap_subtree_max(ptreap->left);
		}
	}

private:
	node_pointer _pnode;
};

template<class U>
bool operator==(const TreavlIter<U> &lhs, const TreavlIter<U> &rhs) {
	return (lhs.base() == rhs.base())
}
template<class U>
bool operator!=(const TreavlIter<U> &lhs, const TreavlIter<U> &rhs) {
	return (lhs.base() != rhs.base())
}

}