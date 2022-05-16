#pragma once

// contrucotr with iterators
// assign with iterators
// 3 types of insert with iterator
// 2 types erase with iterator
// may be data need

#include <iostream>
#include <memory>
#include "iterators.hpp"
#include "utils.hpp"
#include "pair.hpp"

namespace ft{

template <typename T, typename Alloc = std::allocator<T> >
class vector {
public:
	/*------ALIASES------*/
	typedef	T			value_type;
	typedef	Alloc		allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef vector_iterator<pointer> iterator;
	typedef vector_iterator<const_pointer> const_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;


private:
	size_type					_sz;		// Number of T value inside
	size_type					_cap;	// Allocated place
	//std::allocator<value_type>	_alloc;	// Copy of alloc_type object
	Alloc	_alloc;
	pointer						_arr;	// Pointer on an array of T values

public:

	/* Constructors, destructor and assignment(=) */
	vector(const allocator_type& alloc = allocator_type()) : _sz(0), _cap(0), _alloc(alloc)
	{
		_arr = _alloc.allocate(_cap);
	}
	
	vector(size_type n, const_reference value = value_type(), const allocator_type& alloc = allocator_type()) : _sz(n), _cap(n), _alloc(alloc)
	{
		_arr = _alloc.allocate(_cap);
		for (size_t i = 0; i < _sz; ++i)
		{
			_alloc.construct(_arr + i, value);
		}
	}

	template<class InputIt>
	vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIt>::value, bool>::type = true) : _sz(0), _cap(0), _alloc(alloc), _arr(_alloc.allocate(last - first)) {
		assign(first, last);
	}

	//construcotr with iterators!!!

	vector(const vector& orig) : _sz(orig._sz), _cap(orig._cap), _alloc(orig._alloc)
	{
		_arr = _alloc.allocate(_cap);

		for (size_t i = 0; i < orig._sz; ++i)
		{
			_alloc.construct(_arr + i, orig[i]);
		}
	}

	vector<T, Alloc>& operator=(const vector<T, Alloc>& another) {
		if (this == &another) return *this;
		clear();

		//AllocTraits::propagate_on_container_copy_assignment::value
		_alloc = another._alloc;
		reserve(another._cap);

		for (size_t i = 0; i < another.size(); ++i)
		{
			push_back(another[i]);
		}
		return *this;
	}
	
	~vector() {
		clear();
		_alloc.deallocate(_arr, _cap);
	}

	iterator begin() {return (iterator(_arr));};
	const_iterator begin() const {return (const_iterator(_arr));};

	iterator end() {return (iterator(_arr + _sz));};
	const_iterator end() const {return (const_iterator(_arr + _sz));};
	
	reverse_iterator rbegin() {return (reverse_iterator(end()));};
	const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));};

	reverse_iterator rend() {return (reverse_iterator(begin()));};
	const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));};
	
	size_t size() const {
		return _sz;
	}
	
	size_t max_size() const {
		return _alloc.max_size();
	}

	void resize(size_t n, value_type value = T())
	{
		if (n > _cap) 
			reserve(n);
		while (n > _sz)
			push_back(value);
		while (n < _sz)
			pop_back();
	}

	size_t capacity() const {
		return _cap;
	}

	bool empty() const {
		return (_sz == 0);
	}

	void reserve(size_t n)
	{
		if (n <= _cap) return;

		T* newarr = _alloc.allocate(n);

		size_t i = 0;
		try {
			for (; i < _sz; ++i) {
				//AllocTraits::construct(alloc, newarr + i, arr[i]);
				_alloc.construct(newarr + i, _arr[i]);
			}
		} catch (...) {
			for (size_t j = 0; j < i; ++j) {
				//AllocTraits::destroy(alloc, newarr + j);
				_alloc.destroy(newarr + j);
			}
			//AllocTraits::deallocate(newarr, n);
			_alloc.deallocate(newarr, n);
			throw;
		}
		for (size_t i = 0; i < _sz; ++i)
		{
			//AllocTraits::destroy(alloc, arr+i);
			_alloc.destroy(_arr+i);
		}
		//AllocTraits::deallocate(arr, n);
		//std::cout << "1!\n";
		_alloc.deallocate(_arr, _cap);
		//std::cout << "2!\n";
		_arr = newarr;
		_cap = n;
	}

	reference operator[](size_t i) { return _arr[i]; }

	reference at(size_t i) {
		if (i >= _sz) throw std::out_of_range("....");
		return _arr[i];
	}

	const_reference operator[](size_t i) const { return _arr[i]; }

	const_reference at(size_t i) const {
		if (i >= _sz) throw std::out_of_range("....");
		return _arr[i];
	}

	reference front() { return _arr[0]; }

	const_reference front() const { return _arr[0]; }

	reference back() { return _arr[_sz - 1]; }

	const_reference back() const { return _arr[_sz - 1]; }

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
	{
		clear();
		size_t count = last - first;
		size_t old_sz = _sz;
		if (count > _cap)
			reserve(count);
		for (size_t i = 0; i < count; ++i)
		{
			_alloc.construct(_arr + i, *first);
			first++;
		}
		if (old_sz > count)
		{
			for (size_t i = count; i < old_sz; ++i)
			{
				_alloc.destroy(_arr+i);
			}
		}
		_sz = count;
	}

	void assign(size_t n, const T& val) {
		clear();

		if (n > _cap) {
			_alloc.deallocate(_arr, _cap);
			_arr = _alloc.allocate(n);
		}

		for (size_t i = 0; i < n; ++i) {
			_alloc.construct(_arr + i, val);
		}
		_sz = n;
	}

	void push_back(const T& value) {
		if (_cap == 0) reserve(1);
		else if (_sz == _cap) reserve(2 * _cap);
		//AllocTraits::construct(alloc, arr+sz, value);
		_alloc.construct(_arr+_sz, value);
		++_sz;
	}

	void pop_back() {
		//AllocTraits::destroy(alloc, arr + sz - 1);
		_alloc.destroy(_arr+_sz-1);
		--_sz;
	}

	template <class InputIt>
	void insert(iterator pos, InputIt first, InputIt last)
	{
		size_t diff = last - first;
		if (diff < 0)
			throw std::range_error("...");
		if (!diff)
			return ;
		size_t position = pos - begin();
		if (diff + _sz > _cap)
			reserve(diff + _sz);
		for (size_t j = _sz; j > position; j--)
		{
			_alloc.construct(&this->_arr[j - 1 + diff], this->_arr[j - 1]);
		}
		_sz += diff;
		while (diff--)
		{
			_alloc.construct(&this->_arr[position + diff], *--last);
		}
	}

	iterator insert(iterator position, const value_type &val)
	{
		size_t pos = position - begin();
		if (_sz + 1 > _cap)
			reserve(_sz+1);
		for (size_t j = _sz; j > pos; j--)
		{
			_alloc.construct(&this->_arr[j], this->_arr[j - 1]);
		}
		_alloc.construct(&this->_arr[pos], val);
		_sz++;
		return iterator(_arr + pos);
	}

	void insert(iterator position, size_t n, const value_type &val)
	{
		if (!n)
			return;
		size_t required = _sz + n;
		size_t pos = position - begin();
		if (required > _cap)
			reserve(required);
		for (size_t j = _sz; j > pos; j--)
		{
			_alloc.construct(&this->_arr[j - 1 + n], this->_arr[j - 1]);
		}
		_sz += n;
		while (n--)
		{
			_alloc.construct(&this->_arr[pos + n], val);
		}
	}

	iterator erase(iterator position)
	{
		size_t i = position - begin();

		if (!_sz || i >= _sz)
			return position;
		while (i < _sz - 1)
		{
			_alloc.destroy(_arr + i);
			_alloc.construct(_arr + i, _arr[i + 1]);
			i++;
		}
		if (!--_sz)
			return end();
		return position;
	}

	iterator erase(iterator first, iterator second)
	{
		if (!_sz)
			return first;
		difference_type diff = second - first;
		if (diff < 0L)
			throw std::range_error("...");
		size_t pos = first - begin();
		if (diff < 0)
			throw std::range_error("...");
		else if (!diff || pos >= _sz)
			return end();
		size_t count = static_cast<size_t>(diff);
		for (size_t j = pos; j < _sz - count; j++)
		{
			_alloc.destroy(_arr + j);
			_alloc.construct(_arr + j, _arr[j + count]);
		}
		for (size_t i = pos + count; i < _sz; i++)
		{
			_alloc.destroy(_arr + i);
		}
		_sz -= count;
		return first;
	}

	void clear() {
		while (_sz)
			pop_back();
	}

	void swap(vector& x)
	{
		ft::swap(_alloc, x._alloc);
		ft::swap(_arr, x._arr);
		ft::swap(_sz, x._sz);
		ft::swap(_cap, x._cap);
	}

	allocator_type get_allocator() const { return _alloc; }
};

	template <typename T, class Alloc>
	bool operator==(vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T, class Alloc>
	bool operator!=(vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename T, class Alloc>
	bool operator<(vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, class Alloc>
	bool operator<=(vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename T, class Alloc>
	bool operator>(vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, class Alloc>
	bool operator>=(vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}