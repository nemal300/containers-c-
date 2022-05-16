#pragma once

namespace ft {
	template<class F, class S>
	struct pair {
		typedef F first_type;
		typedef S second_type;

		first_type first;
		second_type second;
		
		pair(const first_type &a = first_type(), const second_type &b = second_type()) : first(a), second(b) {

		}

		template<class U, class V>
		pair(const pair<U, V>& other) : first(other.first), second(other.second) {

		}

		pair& operator=(const pair& other) {
			if (this != &other) {
				first = other.first;
				second = other.second;
			}
			return *this;
		}
	};

	template<class F, class S>
	bool operator==(const pair<F, S>& lhs, const pair<F, S>& rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template<class F, class S>
	bool operator!=(const pair<F, S>& lhs, const pair<F, S>& rhs) {
		return !(lhs == rhs);
	}

	template<class F, class S>
	bool operator<(const pair<F, S>& lhs, const pair<F, S>& rhs) {
		if (lhs.first < rhs.first) {
			return true;
		} else if (lhs.first == rhs.first){
			if (lhs.second < rhs.second)
				return true;
		}
		return false;
	}

	template<class F, class S>
	bool operator<=(const pair<F, S>& lhs, const pair<F, S>& rhs) {
		return !(rhs < lhs);
	}
	
	template<class F, class S>
	bool operator>(const pair<F, S>& lhs, const pair<F, S>& rhs) {
		return (rhs < lhs);
	}

	template<class F, class S>
	bool operator>=(const pair<F, S>& lhs, const pair<F, S>& rhs) {
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	ft::pair<T1, T2> make_pair(const T1 &x, const T2 &y)
	{
		return (pair<T1, T2>(x, y));
	}
}