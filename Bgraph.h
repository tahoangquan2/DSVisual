#include "constant.h"

// backend for graph
namespace Bgraph {
	struct Node {
		short value;
		Node* next;
	};

	short a_size = 0, b_size = 0, current, a[15], b[15], value, position, mode;
	bool move;
	Node* Head = nullptr;
};
