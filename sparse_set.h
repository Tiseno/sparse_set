#pragma once

#include <iostream>
#include <vector>

template<typename D>
struct SparseSetData {
	size_t index;
	D data;
};

template<typename D>
std::ostream &operator<<(std::ostream &os, SparseSetData<D> const& m) {
	return os << "\033[30;1m#" << m.index << "\033[0m" << m.data;
}

size_t INVALID_INDEX = -1;
template<typename D>
struct SparseSet {
	std::vector<SparseSetData<D>> dense;
	std::vector<size_t> sparse;

	D* assign(size_t index, D d) {
		if(sparse.size() <= index) {
			sparse.resize((index+1) * 1.2, INVALID_INDEX);
		}
		if (lookup(index)) {
			dense[sparse[index]].data = d;
		} else {
			sparse[index] = dense.size();
			dense.push_back(SparseSetData<D>{index, d});
		}

		return get(index);
	}

	void remove(size_t index) {
		if (dense.size() == 0 || !lookup(index)) {
			return;
		}
		dense[sparse[index]] = dense.back();
		sparse[dense.back().index] = sparse[index];
		dense.pop_back();
	}

	bool lookup(size_t index) {
		return sparse[index] < dense.size() && dense[sparse[index]].index == index;
	}

	D* get(size_t index) {
		if(lookup(index)) {
			return &dense[sparse[index]].data;
		}
		return nullptr;
	}
};

