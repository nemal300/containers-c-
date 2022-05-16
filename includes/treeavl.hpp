#pragma once

#include <iostream>

namespace ft {
	
template<typename value_type>
struct _node {
	value_type value;
	size_t height;
	_node<value_type>* left;
	_node<value_type>* right;
	_node<value_type>* parent;

	_node(const value_type& val) : value(val), height(1), left(NULL), right(NULL), parent(NULL) {}

	_node(const _node& copy) : value(copy.value), height(copy.height), left(copy.left), right(copy.right), parent(copy.parent) {}

	_node& operator=(const _node& oth) {
		if (this != &other)
			*this = oth;
		return *this;
	}

	~node(){}
};

template<typename value, class Compare = std::less<value>, class Alloc = std::allocator<value> >
class Treavl {
public:
	typedef value value_type;
	typedef Alloc allocator_type;
	typedef Compare compare_type;
	typedef _node<value_type> node_type;

	typedef typename allocator_type::template rebind<node_type>::other node_allocator;
	typedef typename node_allocator::difference_type difference_type;
	typedef typename node_allocator::size_type size_type;
	typedef typename node_allocator::pointer node_pointer;
	typedef typename node_allocator::const_pointer const_node_pointer;
	typedef typename node_allocator::reference node_reference;
	typedef typename node_allocator::const_reference const_node_reference;

	typedef TreavlIter<value_type> iterator;
	typedef TreavlIter<const value_type> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
public:
	Treavl(const compare_type& cmp, const allocator_type& alloc = allocator_type()) : _alloc(alloc), _node_alloc(node_allocator()), _cmp(cmp), _sz(0) {
		_header = _node_alloc.allocate(1);
		_node_alloc.construct(_header, value_type());
		_root = _header;
	}

	Treavl(const Treavl& other) : _alloc(other._alloc), _node_alloc(other._alloc), _cmp(other._cmp), _sz(0) {
		if (this != &other) {
			_header = node_allocator.allocate(1);
			_node_alloc.construct(_header, value_type());
			_root = _header;
			_insert_all_nodes(_root, other._root);
		}
	}

	Treavl& operator=(const Treap& other) {
		if (this != &other) {
			_alloc = other._allocator;
			_node_alloc = other._node_allocator;
			_cmp = other._cmp;
			_sz = other._sz;
			if (_root != _header) {
				_delete_treap(_root);
			}
			_root = _header;
			_header->left = nullptr;
			_header->right = nullptr;
			if (other.size > 0) {
				_insert_all_nodes(_root, other._root);
			}
		}
		return *this;
	}

	~Treavl() {
		if (_root != _header)
			_delete_treap(_root);
		node_allocator.destroy(_header);
		node_allocator.deallocate(_header, 1);
	}

	iterator begin() {return iterator(_subtree_min(_root));}
	const_iterator begin() const {return const_iterator(_subtree_min(_root));}
	iterator end() {return iterator(_header);}
	const_iterator end() const {return const_iterator(_header);}
	reverse_iterator rbegin() {return reverse_iterator(end());}
	const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
	reverse_iterator rend() {return reverse_iterator(begin());}
	const_reverse_iterator rend() {return reverse_iterator(begin());}

	size_t size() const {
		return _sz;
	}

	void clear() {
		if (_root != _header) {
			_delete_treap(_root);
			_sz = 0;
			_root = _header;
			_header->left = _header->right = nullptr;
		}
	}

	ft::pair<iterator, bool> insert(const value_type& value) {
		node_pointer pnode = nullptr;
		if (_root != _header) {
			pnode = _search(_root, value);
		}
		if (pnode) {
			return ft::make_pair(iterator(pnode), false);
		}
		else {
			_insert_avl(value);
			return ft::make_pair(iterator(_search(_root, value)), true);
		}
	}
	iterator insert(iterator hint, const value_type& value) {
		(void)hint;
		return insert(value).first;
	}
	
	size_type erase(iterator pos) {
		if (pos != end()) {
			_root = __erase(_root, pos.base()->value);
			_assign_paths_header();
			--_sz;
			return 1;
		}
		else
			return 0;
	}
	iterator find(const value_type& value) {
		node_pointer pnode = _search(_root, value);
		if (pnode) {
			return iterator(pnode);
		}
		else {
			return end();
		}
	}

	const_iterator find(const value_type& value) const {
		node_pointer pnode = _search(_root, value);
		if (pnode) {
			return const_iterator(pnode);
		}
		else {
			return end();
		}
	}

	iterator lower_bound(const value_type& value) {
		node_pointer less = nullptr;
		if (_cmp(*--end(), value)) {
			return end();
		}
		_first_less_than(_root, value, less);
		if (less) {
			return iterator(less);
		}
		else {
			return begin();
		}
	}

	iterator lower_bound(const value_type& value) {
		node_pointer less = nullptr;
		if (_cmp(*--end(), value)) {
			return end();
		}
		_first_less_than(_root, value, less);
		if (less) {
			return const_iterator(less);
		}
		else {
			return begin();
		}
	}

	iterator upper_bound(const value_type& value) {
		node_pointer greater = nullptr;
		_first_greater_than(_root, value, greater);
		if (greater) {
			return iterator(greater);
		} else {
			return end();
		}
	}

	const_iterator upper_bound(const value_type& value) const {
		node_pointer greater = nullptr;
		_first_greater_than(_root, value, greater);
		if (greater) {
			return const_iterator(greater);
		} else {
			return end();
		}
	}

	void swap(Treavl& other) {
		ft::swap(_alloc, other._alloc);
		ft::swap(_node_alloc, other._node_alloc);
		ft::swap(_cmp, other._cmp);
		ft::swap(_root, other._root);
		ft::swap(_header, other._header);
		ft::swap(_sz, other._sz);
	}
private:

	size_t _height(node_pointer p) {
		if (p) {
			return p->height;
		}
		else
			return 0;
	}

	int _bfactor(node_pointer p) {
		return _height(p->right) - _height(p->left);
	}

	void _fix_height(node_pointer p) {
		size_t hl = _height(p->l);
		size_t hr = _height(p->r);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	node_pointer _rotate_right(node_pointer p) {
		node_pointer q = p->left;
		q->parent = p->parent;
		p->left = q->right;
		if (q->right) {
			q->right->parent = p;
		}
		q->right = p;
		p->parent = q;
		_fix_height(p);
		_fix_height(q);
		return q;
	}

	node_pointer _rotate_left(node_pointer q) {
		node_pointer p = q->right;
		p->parent = q->parent;
		q->right = p->left;
		if (p->left) {
			p->left->parent = q;
		}
		p->left = q;
		q->parent = p;
		_fix_height(q);
		_fix_height(p);
		return p;
	}

	node_pointer _balance(node_pointer p) {
		_fix_height(p);
		if (_bfactor(p) == 2) {
			if (_bfactor(pnode->right) < 0) {
				pnode->right = _rotate_right(pnode->right);
			}
			return _rotate_left(p);
		}
		if (_bfactor(p) == -2 ) {
			if (_bfactor(pnode->left) > 0) {
				pnode->left = _rotate_left(pnode->left);
			}
			return _rotate_right(p);
		}
		return p;
	}

	node_pointer _subtree_min(node_pointer treap) const {
		while (treap->left) {
			treap = treap->left;
		}
		return treap;
	}

	node_pointer _erase_subtree_min(node_pointer p) {
		if (!p->left) {
			return p->right;
		}
		p->left = _erase_subtree_min(p->left);
		if (p->left) {
			p->left->parent = p;
		}
		return _balance(p);
	}

	node_pointer __erase(node_pointer pnode, const value_type& value) {
		if (!pnode) {
			return nullptr;
		}
		if (_cmp(value, pnode->value)) {
			pnode->left = __erase(pnode->left, value);
			if (pnode->left) {
				pnode->left->parent = pnode;
			}
		}
		else if (_cmp(pnode->value, value)) {
			pnode->right = __erase(pnode->right, value);
			if (pnode->right) {
				pnode->right->parent = pnode;
			}
		}
		else {
			node_pointer q = pnode->left;
			node_pointer r = pnode->right;
			if (!r) {
				if (q) {
					q->parent pnode->parent;
				}
				_node_alloc.destroy(pnode);
				_node_alloc.deallocate(pnode, 1);
				return q;
			}
			node_pointer min = _subtree_min(r);
			min->right = _erase_subtree_min(r);
			if (min->right) {
				min->right->parent = min;
			}
			min->left = q;
			if (q)
				q->parent = min;
			return _balance(min);
		}
		return _balance(pnode);
	}

	node_pointer __insert(node_pointer root, const value_type& val) {
		if (!root) {
			root = _node_alloc.allocate(1);
			_node_alloc.construct(root, val);
		}
		else {
			if (_cmp(val, root->value)) {
				root->left = __insert(root->left, val);
				root->left->parent = root;
			}
			else if (_cmp(root->value, val)) {
				root->right = __insert(root->right, val);
				root->rigth->parent = root;
			}
		}
		return _balance(root);
	}

	void _assign_paths_header() {
		_header->left = _root;
		_header->right = _root;
		if (_root) {
			_root->parent = _header;
		}
	}

	void _insert_avl(const value_type& val) {
		if (_root == _header) {
			_root = __insert(nullptr, val);
			_assign_paths_header();
			++_sz;
		}
		else if (!_search(_root, val)) {
			_root = __insert(_root, val);
			assign_paths_header();
		}
	}

	void _insert_all_nodes(node_pointer to, node_pointer from) {
		if (from) {
			_insert_avl(from->value);
			_insert_all_nodes(to, from->left);
			_insert_all_nodes(to, from->right);	
		}
	}

	void _delete_treap(node_pointer node) {
		if (node) {
			_delete_treap(node->left);
			_delete_treap(node->right);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node,1)l
		}
	}

	node_pointer _search(node_pointer treap, const value_type& target) const {
		if (!treap) {
			return nullptr;
		}
		else {
			if (_cmp(target, treap->value)) {
				return _search(treap->left, target);
			}
			else if (_cmp(treap->value, target)) {
				return _search(treap->right, target);
			}
			else {
				return treap;
			}
		}
	}

	void _first_less_than(node_pointer pnode, const value_type& than, node_pointer& less) const {
	if (pnode) {
		if (_cmp(than, pnode->value)) {
			_first_less_than(pnode->left, than, less);
		} else if (_cmp(pnode->value, than)) {
			less = _max_node(less, pnode);
			_first_less_than(pnode->right, than, less);
		} else {
			less = pnode;
		}
	}
}

void _first_greater_than(node_pointer pnode, const value_type& than, node_pointer& greater) const {
	if (pnode) {
		if (_cmp(than, pnode->value)) {
			greater = _min_node(greater, pnode);
			_first_greater_than(pnode->left, than, greater);
		} else {
			_first_greater_than(pnode->right, than, greater);
		}
	}
}

private:
	allocator_type _alloc;
	node_allocator _node_alloc;
	compare_type _cmp;
	node_pointer _root;
	node_pointer _header;
	size_type _sz;
};

}