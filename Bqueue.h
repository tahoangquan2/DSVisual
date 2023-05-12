#include "constant.h"

// backend for queue
namespace Bqueue {
	struct Node {
		short value;
		Node* next;
	};

	short a_size = 0, b_size = 0, current, a[15], b[15], value, position, mode;
	bool move;
	Node* Head = nullptr;

	short Size() {
		if (Head == nullptr) {
			return 0;
		}

		short cnt = 0;
		Node* head = Head;
		while (head != nullptr) {
			++cnt;
			head = head->next;
		}

		return cnt;
	}

	short Value(short pos) {
		if (Head == nullptr) {
			return -1000;
		}

		Node* head = Head;
		for (short i = 1; i <= pos; ++i) {
			if (head->next == nullptr) {
				return -1000;
			}
			head = head->next;
		}

		return head->value;
	}

	short Search(short val) {
		if (Head == nullptr) {
			return -1;
		}

		Node* head = Head;
		short cnt = 0;
		while (head != nullptr) {
			if (head->value == val) {
				return cnt;
			}
			++cnt;
			head = head->next;
		}

		return -1;
	}

	void Update(short pos, short val) {
		if (Head == nullptr) {
			return;
		}

		if (pos == 1) {
			Head->value = val;
		}

		Node* head = Head;
		for (short i = 1; i < pos; ++i) {
			if (head->next == nullptr) {
				return;
			}
			head = head->next;
		}

		head->value = val;
	}

	void Delete(short pos) {
		if (Head == nullptr) {
			return;
		}

		if (pos == 1) {
			Node* head = Head;
			Head = Head->next;
			delete head;
			return;
		}

		Node* head = Head;
		for (short i = 1; i < pos - 1; ++i) {
			if (head->next == nullptr) {
				return;
			}
			head = head->next;
		}

		Node* temp = head->next;
		head->next = temp->next;
		delete temp;
	}

	void Insert(short pos, short val) {
		Node* newnode = new Node;
		newnode->value = val;
		newnode->next = nullptr;

		if (Head == nullptr) {
			Head = newnode;
			return;
		}

		if (pos == 1) {
			newnode->next = Head;
			Head = newnode;
			return;
		}

		Node* head = Head;
		for (short i = 1; i < pos - 1; ++i) {
			if (head->next == nullptr) {
				return;
			}
			head = head->next;
		}

		newnode->next = head->next;
		head->next = newnode;
	}

	void Erase() {
		Node* head = Head;
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		Head = nullptr;
	}

	void Apply() {
		a_size = 0;
		Node* head = Head;
		while (head != nullptr) {
			a[++a_size] = head->value;
			head = head->next;
		}
	}

	void Reverse() {
		Erase();
		Node* head = Head;
		for (short i = 1; i <= a_size; ++i) {
			Insert(i, a[i]);
		}
	}

	bool addBox(short val = 0) {
		if (a_size == max_size) {
			wxMessageBox(wxT("The maximum number of element you can have is 12"), wxT("Error"), wxICON_ERROR);

			return false;
		}

		++a_size;
		a[a_size] = val;

		return true;
	}

	bool insertPosition(short pos, short val) {
		if (Size() == max_size) {
			return false;
		}

		Insert(pos, val);
		Apply();

		return true;
	}

	bool deletePosition(short pos) {
		Delete(pos);
		Apply();

		return true;
	}

	bool setup(short pos, int val, short signal) {
		position = pos;
		value = val;
		mode = signal;
		move = false;
		b_size = a_size;

		for (short i = 1; i <= a_size; ++i) {
			b[i] = a[i];
		}

		b[b_size + 1] = 0;

		switch (mode) {
		case 1:
			current = 1;
			break;

		case 2:
			current = 1;
			break;

		case 3:
			current = 1;
			break;

		case 4:
			current = 1;
			break;

		case 5:
			current = 1;
			break;
		}

		return true;
	}

	bool next() {
		switch (mode) {
		case 1:
			if (current != position) {
				++current;
			}
			else {
				return true;
			}
			break;

		case 2:
			if (current != position) {
				++current;
			}
			else {
				return true;
			}
			break;

		case 3:
			if (current != position) {
				++current;
			}
			else {
				return true;
			}
			break;

		case 4:
			if (current != position) {
				++current;
			}
			else {
				return true;
			}
			break;

		case 5:
			if (current != b_size) {
				if (b[current] == value) {
					return true;
				}
				else {
					++current;
				}
			}
			else {
				return true;
			}
			break;
		}

		return false;
	}
};
