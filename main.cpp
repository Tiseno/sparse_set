#include <iostream>

#include "sparse.h"

struct SomeData {
	char c;
};

void printSparseSet(SparseSet<SomeData> & sparseSet, bool all = false) {
	std::cout << "dense cap: " << sparseSet.dense.capacity() << " size: " << sparseSet.dense.size() << "\n";
	if (all)
		for (auto e : sparseSet.dense) {
			std::cout << "\t" << e.index << " " << e.data.c << "\n";
		}

	std::cout << "sparse cap: " << sparseSet.sparse.capacity() << " size: " << sparseSet.sparse.size() << "\n";
	if (all) {
		int j = 0;
		for (auto e : sparseSet.sparse) {
			if (e != INVALID_INDEX) {
				std::cout << "\t" << j++ << ": denseIndex(" << e << ")\n";
			}
		}
	}
}

int main() {
	SparseSet<SomeData> sparseSet;
	sparseSet.assign(4, SomeData{'A'});
	sparseSet.assign(6, SomeData{'A'});
	sparseSet.assign(0, SomeData{'A'});
	printSparseSet(sparseSet);

	int i = 0;
	while (true) {
		sparseSet.remove((size_t)(rand() % (int)(100)));
		sparseSet.assign((size_t)(rand() % (int)(100)), SomeData{(char)(65 + (rand() % 25))});

		if (++i % 1000000 == 0)
			printSparseSet(sparseSet, true);
	}

	return 0;
}
