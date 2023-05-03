#include "constant.h"

namespace BstaticArray {
	short a_size = 0, b_size = 0, current, a[15], b[15], value, position, mode;
	bool move;

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
		for (short i = a_size; i >= pos; --i) {
			a[i + 1] = a[i];
		}
		a[pos] = val;
		return true;
	}

	bool deletePosition(short pos) {
		for (short i = pos; i < a_size; ++i) {
			a[i] = a[i + 1];
		}
		a[a_size] = 0;
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
			current = b_size;
			break;
		}
		return true;
	}

	bool next() {
		switch (mode) {
		case 1:
			if (current != position) {
				if (move == false) {
					move = true;
					--current;
				}
				else {
					move = false;
					b[current + 1] = b[current];
					b[current] = 0;
				}
			}
			else {
				if (move == true) {
					move = false;
					b[current + 1] = b[current];
					b[current] = 0;
				}
				else {
					b[current] = value;
					return true;
				}
			}
			break;
		}
		return false;
	}
};