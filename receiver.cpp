#include "receiver.h"

#include "UstaticArray.h"
#include "UdynamicArray.h"
#include "UsimplyLinkedList.h"
#include "UdoublyLinkedList.h"
#include "UcircularLinkedList.h"
#include "Ustack.h"
#include "Uqueue.h"

#include "BstaticArray.h"
#include "BdynamicArray.h"
#include "BsimplyLinkedList.h"
#include "BdoublyLinkedList.h"
#include "BcircularLinkedList.h"
#include "Bstack.h"
#include "Bqueue.h"

// get a random number in range [l, r]
short getRandom(short l, short r) {
	return (rand() % (r - l + 1)) + l;
}

// show an error for debugging and announcement 
void showError(wxString message) {
	wxMessageBox(message, wxT("Error"), wxICON_ERROR);
}

// draw the box frame
void drawBox(wxPanel** boxs, wxPanel* base, short pos, short val = -1000, short mode = 0) {
	if (pos > max_size) {
		return;
	}

	if (val == -1000) {
		if (boxs[pos] != nullptr) {
			boxs[pos]->Destroy();
			boxs[pos] = nullptr;
		}

		return;
	}

	boxs[pos] = new wxPanel(base, wxID_ANY, wxPoint(box_position[pos], box_y), wxSize(box_size, box_size), wxBORDER_DOUBLE);
	boxs[pos]->SetBackgroundColour(wxColour(box_color, box_color, box_color));

	wxString display_value = "";
	display_value << val;
	wxStaticText* text = new wxStaticText(boxs[pos], wxID_ANY, display_value);
	text->Center();
}

// draw the arrow in the step by step mode
void drawArrow(wxStaticBitmap* arrow, short pos) {
	arrow->Show();
	arrow->SetPosition(wxPoint(box_position[pos] + 10, box_y - 50));
}

// change menu frame and chosen frame
void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel) {
	current_panel->Hide();
	goto_panel->Show();
}

// clear the array in the backend
void rClear(short id, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case id_static_array:
		for (short i = 1; i <= BstaticArray::a_size; ++i) {
			BstaticArray::a[i] = -1000;
			drawBox(boxs, base, i);
		}
		BstaticArray::a_size = 0;
		break;

	case id_dynamic_array:
		for (short i = 1; i <= BdynamicArray::a_size; ++i) {
			BdynamicArray::a[i] = -1000;
			drawBox(boxs, base, i);
		}
		BdynamicArray::a_size = 0;
		break;

	case id_simply_linked_list:
		for (short i = 1; i <= BsimplyLinkedList::a_size; ++i) {
			BsimplyLinkedList::a[i] = -1000;
			drawBox(boxs, base, i);
		}
		BsimplyLinkedList::Erase();
		BsimplyLinkedList::Apply();
		break;

	case id_doubly_linked_list:
		for (short i = 1; i <= BdoublyLinkedList::a_size; ++i) {
			BdoublyLinkedList::a[i] = -1000;
			drawBox(boxs, base, i);
		}
		BdoublyLinkedList::Erase();
		BdoublyLinkedList::Apply();
		break;

	case id_circular_linked_list:
		for (short i = 1; i <= BcircularLinkedList::a_size; ++i) {
			BcircularLinkedList::a[i] = -1000;
			drawBox(boxs, base, i);
		}
		BcircularLinkedList::Erase();
		BcircularLinkedList::Apply();
		break;

	case id_stack:
		for (short i = 1; i <= Bstack::a_size; ++i) {
			Bstack::a[i] = -1000;
			drawBox(boxs, base, i);
		}
		Bstack::Erase();
		Bstack::Apply();
		break;

	case id_queue:
		for (short i = 1; i <= Bqueue::a_size; ++i) {
			Bqueue::a[i] = -1000;
			drawBox(boxs, base, i);
		}
		Bqueue::Erase();
		Bqueue::Apply();
		break;
	}
}

// create random input in the backend
void rCreateRandom(short id, wxPanel** boxs, wxPanel* base) {
	short random_size = getRandom(3, 12);

	switch (id) {
	case id_static_array:
		for (short i = 1; i <= random_size; ++i) {
			BstaticArray::addBox(getRandom(1, 69));
			drawBox(boxs, base, i, BstaticArray::a[i]);
		}
		break;

	case id_dynamic_array:
		for (short i = 1; i <= random_size; ++i) {
			BdynamicArray::addBox(getRandom(1, 69));
			drawBox(boxs, base, i, BdynamicArray::a[i]);
		}
		break;


	case id_simply_linked_list:
		for (short i = 1; i <= random_size; ++i) {
			BsimplyLinkedList::addBox(getRandom(1, 69));
			drawBox(boxs, base, i, BsimplyLinkedList::a[i], 1);
		}
		BsimplyLinkedList::Reverse();
		break;

	case id_doubly_linked_list:
		for (short i = 1; i <= random_size; ++i) {
			BdoublyLinkedList::addBox(getRandom(1, 69));
			drawBox(boxs, base, i, BdoublyLinkedList::a[i], 1);
		}
		BdoublyLinkedList::Reverse();
		break;

	case id_circular_linked_list:
		for (short i = 1; i <= random_size; ++i) {
			BcircularLinkedList::addBox(getRandom(1, 69));
			drawBox(boxs, base, i, BcircularLinkedList::a[i], 1);
		}
		BcircularLinkedList::Reverse();
		break;

	case id_stack:
		for (short i = 1; i <= random_size; ++i) {
			Bstack::addBox(getRandom(1, 69));
			drawBox(boxs, base, i, Bstack::a[i], 1);
		}
		Bstack::Reverse();
		break;

	case id_queue:
		for (short i = 1; i <= random_size; ++i) {
			Bqueue::addBox(getRandom(1, 69));
			drawBox(boxs, base, i, Bqueue::a[i], 1);
		}
		Bqueue::Reverse();
		break;
	}
}

// change the string input from file to a readable value for backend
void rStringToBox(short id, std::string& line, wxPanel** boxs, wxPanel* base) {
	short value[15] = {};
	short sz = 0;

	if (line.size() > 60) {
		showError("Input is too long");
		return;
	}

	for (short i = 0; i < line.size(); ++i) {
		if (line[i] == ',') {
			++sz;
			if (sz > 12) {
				break;
			}
		}
		else if ('0' <= line[i] && line[i] <= '9') {
			value[sz] = value[sz] * 10 + short(line[i]) - short('0');
			if (value[sz] < -999 || value[sz] > 999) {
				showError("Value must be in range [-999, 999]");
				return;
			}
		}
		else {
			showError("Value input must be numbers seperated with comma (',')");
			return;
		}
	}

	switch (id) {
	case id_static_array:
		for (short i = 1; i <= sz; ++i) {
			BstaticArray::addBox(value[i]);
			drawBox(boxs, base, i, BstaticArray::a[i]);
		}
		break;

	case id_dynamic_array:
		for (short i = 1; i <= sz; ++i) {
			BdynamicArray::addBox(value[i]);
			drawBox(boxs, base, i, BdynamicArray::a[i]);
		}
		break;


	case id_simply_linked_list:
		for (short i = 1; i <= sz; ++i) {
			BsimplyLinkedList::addBox(value[i]);
			drawBox(boxs, base, i, BsimplyLinkedList::a[i]);
		}
		BsimplyLinkedList::Reverse();
		break;

	case id_doubly_linked_list:
		for (short i = 1; i <= sz; ++i) {
			BdoublyLinkedList::addBox(value[i]);
			drawBox(boxs, base, i, BdoublyLinkedList::a[i]);
		}
		BdoublyLinkedList::Reverse();
		break;

	case id_circular_linked_list:
		for (short i = 1; i <= sz; ++i) {
			BcircularLinkedList::addBox(value[i]);
			drawBox(boxs, base, i, BcircularLinkedList::a[i]);
		}
		BcircularLinkedList::Reverse();
		break;

	case id_stack:
		for (short i = 1; i <= sz; ++i) {
			Bstack::addBox(value[i]);
			drawBox(boxs, base, i, Bstack::a[i]);
		}
		Bstack::Reverse();
		break;

	case id_queue:
		for (short i = 1; i <= sz; ++i) {
			Bqueue::addBox(value[i]);
			drawBox(boxs, base, i, Bqueue::a[i]);
		}
		Bqueue::Reverse();
		break;
	}
}

// insert a value to a specific position in the backend
void rInsert(short id, short pos, short val, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::insertPosition(pos, val);
		for (short i = 1; i <= BstaticArray::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, BstaticArray::a[i]);
		}
		break;

	case id_dynamic_array:
		++pos;
		BdynamicArray::insertPosition(pos, val);
		for (short i = 1; i <= BdynamicArray::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, BdynamicArray::a[i]);
		}
		break;


	case id_simply_linked_list:
		++pos;
		if (BsimplyLinkedList::insertPosition(pos, val) == false) {
			showError("The maximum number of element you can have is 12");
			return;
		}

		for (short i = 1; i <= BsimplyLinkedList::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, BsimplyLinkedList::a[i], 1);
		}
		break;

	case id_doubly_linked_list:
		++pos;
		if (BdoublyLinkedList::insertPosition(pos, val) == false) {
			showError("The maximum number of element you can have is 12");
			return;
		}

		for (short i = 1; i <= BdoublyLinkedList::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, BdoublyLinkedList::a[i], 1);
		}
		break;

	case id_circular_linked_list:
		++pos;
		if (BcircularLinkedList::insertPosition(pos, val) == false) {
			showError("The maximum number of element you can have is 12");
			return;
		}

		for (short i = 1; i <= BcircularLinkedList::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, BcircularLinkedList::a[i], 1);
		}
		break;

	case id_stack:
		if (Bstack::insertPosition(pos, val) == false) {
			showError("The maximum number of element you can have is 12");
			return;
		}

		for (short i = 1; i <= Bstack::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, Bstack::a[i], 1);
		}
		break;

	case id_queue:
		if (Bqueue::insertPosition(pos, val) == false) {
			showError("The maximum number of element you can have is 12");
			return;
		}

		for (short i = 1; i <= Bqueue::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, Bqueue::a[i], 1);
		}
		break;
	}
}

// delete a value to a specific position in the backend
void rDelete(short id, short pos, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::deletePosition(pos);
		for (short i = 1; i <= BstaticArray::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, BstaticArray::a[i]);
		}
		break;

	case id_dynamic_array:
		++pos;
		BdynamicArray::deletePosition(pos);
		for (short i = 1; i <= BdynamicArray::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, BdynamicArray::a[i]);
		}
		break;


	case id_simply_linked_list:
		++pos;
		for (short i = 1; i <= BsimplyLinkedList::a_size; ++i) {
			drawBox(boxs, base, i);
		}
		BsimplyLinkedList::deletePosition(pos);
		for (short i = 1; i <= BsimplyLinkedList::a_size; ++i) {
			drawBox(boxs, base, i, BsimplyLinkedList::a[i], 1);
		}
		break;

	case id_doubly_linked_list:
		++pos;
		for (short i = 1; i <= BdoublyLinkedList::a_size; ++i) {
			drawBox(boxs, base, i);
		}
		BdoublyLinkedList::deletePosition(pos);
		for (short i = 1; i <= BdoublyLinkedList::a_size; ++i) {
			drawBox(boxs, base, i, BdoublyLinkedList::a[i], 1);
		}
		break;

	case id_circular_linked_list:
		++pos;
		for (short i = 1; i <= BcircularLinkedList::a_size; ++i) {
			drawBox(boxs, base, i);
		}
		BcircularLinkedList::deletePosition(pos);
		for (short i = 1; i <= BcircularLinkedList::a_size; ++i) {
			drawBox(boxs, base, i, BcircularLinkedList::a[i], 1);
		}
		break;

	case id_stack:
		for (short i = 1; i <= Bstack::a_size; ++i) {
			drawBox(boxs, base, i);
		}
		Bstack::deletePosition(pos);
		for (short i = 1; i <= Bstack::a_size; ++i) {
			drawBox(boxs, base, i, Bstack::a[i], 1);
		}
		break;

	case id_queue:
		for (short i = 1; i <= Bqueue::a_size; ++i) {
			drawBox(boxs, base, i);
		}
		Bqueue::deletePosition(pos);
		for (short i = 1; i <= Bqueue::a_size; ++i) {
			drawBox(boxs, base, i, Bqueue::a[i], 1);
		}
		break;
	}
}

// update a value to a specific position in the backend
void rUpdate(short id, short pos, short val, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::a[pos] = val;
		drawBox(boxs, base, pos);
		drawBox(boxs, base, pos, BstaticArray::a[pos]);
		break;

	case id_dynamic_array:
		++pos;
		BdynamicArray::a[pos] = val;
		drawBox(boxs, base, pos);
		drawBox(boxs, base, pos, BdynamicArray::a[pos]);
		break;


	case id_simply_linked_list:
		++pos;
		BsimplyLinkedList::Update(pos, val);
		BsimplyLinkedList::Apply();
		drawBox(boxs, base, pos);
		drawBox(boxs, base, pos, BsimplyLinkedList::a[pos], 1);
		break;

	case id_doubly_linked_list:
		++pos;
		BdoublyLinkedList::Update(pos, val);
		BdoublyLinkedList::Apply();
		drawBox(boxs, base, pos);
		drawBox(boxs, base, pos, BdoublyLinkedList::a[pos], 1);
		break;

	case id_circular_linked_list:
		++pos;
		BcircularLinkedList::Update(pos, val);
		BcircularLinkedList::Apply();
		drawBox(boxs, base, pos);
		drawBox(boxs, base, pos, BcircularLinkedList::a[pos], 1);
		break;
	}
}

// search a value in the backend
short rSearch(short id, short val) {
	switch (id) {
	case id_static_array:
		for (short i = 1; i <= BstaticArray::a_size; ++i) {
			if (BstaticArray::a[i] == val) {
				return i - 1;
			}
		}
		break;

	case id_dynamic_array:
		for (short i = 1; i <= BdynamicArray::a_size; ++i) {
			if (BdynamicArray::a[i] == val) {
				return i - 1;
			}
		}
		break;


	case id_simply_linked_list:
		return BsimplyLinkedList::Search(val);
		break;

	case id_doubly_linked_list:
		return BdoublyLinkedList::Search(val);
		break;

	case id_circular_linked_list:
		return BcircularLinkedList::Search(val);
		break;
	}

	return -1;
}

// go to the next step in the backend
bool rNext(short id, wxPanel** boxs, wxPanel* base, wxStaticBitmap* arrow) {
	bool signal;
	switch (id) {
	case id_static_array:
		signal = BstaticArray::next();

		drawArrow(arrow, BstaticArray::current);
		drawBox(boxs, base, BstaticArray::current);
		drawBox(boxs, base, BstaticArray::current, BstaticArray::b[BstaticArray::current]);

		if (BstaticArray::current + 1 <= BstaticArray::b_size) {
			drawBox(boxs, base, BstaticArray::current + 1);
			drawBox(boxs, base, BstaticArray::current + 1, BstaticArray::b[BstaticArray::current + 1]);
		}

		if (signal == true) {
			return true;
		}

		break;

	case id_dynamic_array:
		signal = BdynamicArray::next();

		drawArrow(arrow, BdynamicArray::current);
		drawBox(boxs, base, BdynamicArray::current);
		drawBox(boxs, base, BdynamicArray::current, BdynamicArray::b[BdynamicArray::current]);

		if (BdynamicArray::current + 1 <= BdynamicArray::b_size) {
			drawBox(boxs, base, BdynamicArray::current + 1);
			drawBox(boxs, base, BdynamicArray::current + 1, BdynamicArray::b[BdynamicArray::current + 1]);
		}

		if (signal == true) {
			return true;
		}

		break;


	case id_simply_linked_list:
		signal = BsimplyLinkedList::next();

		drawArrow(arrow, BsimplyLinkedList::current);

		if (signal == true) {
			return true;
		}

		break;

	case id_doubly_linked_list:
		signal = BdoublyLinkedList::next();

		drawArrow(arrow, BdoublyLinkedList::current);

		if (signal == true) {
			return true;
		}

		break;

	case id_circular_linked_list:
		signal = BcircularLinkedList::next();

		drawArrow(arrow, BcircularLinkedList::current);

		if (signal == true) {
			return true;
		}

		break;
	}
}

// insert a value to a specific position in the backend in the step by step mode
void rInsertSbs(short id, short pos, short val, wxStaticBitmap* arrow) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::setup(pos, val, 1);
		drawArrow(arrow, BstaticArray::current);
		break;

	case id_dynamic_array:
		++pos;
		BdynamicArray::setup(pos, val, 1);
		drawArrow(arrow, BdynamicArray::current);
		break;


	case id_simply_linked_list:
		++pos;
		BsimplyLinkedList::setup(pos, val, 1);
		drawArrow(arrow, BsimplyLinkedList::current);
		break;

	case id_doubly_linked_list:
		++pos;
		BdoublyLinkedList::setup(pos, val, 1);
		drawArrow(arrow, BdoublyLinkedList::current);
		break;

	case id_circular_linked_list:
		++pos;
		BcircularLinkedList::setup(pos, val, 1);
		drawArrow(arrow, BcircularLinkedList::current);
		break;
	}
}

// delete a value to a specific position in the backend in the step by step mode
void rDeleteSbs(short id, short pos, wxStaticBitmap* arrow) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::setup(pos, 0, 2);
		drawArrow(arrow, BstaticArray::current);
		break;

	case id_dynamic_array:
		++pos;
		BdynamicArray::setup(pos, 0, 2);
		drawArrow(arrow, BdynamicArray::current);
		break;

	case id_simply_linked_list:
		++pos;
		BsimplyLinkedList::setup(pos, 0, 2);
		drawArrow(arrow, BsimplyLinkedList::current);
		break;

	case id_doubly_linked_list:
		++pos;
		BdoublyLinkedList::setup(pos, 0, 2);
		drawArrow(arrow, BdoublyLinkedList::current);
		break;

	case id_circular_linked_list:
		++pos;
		BcircularLinkedList::setup(pos, 0, 2);
		drawArrow(arrow, BcircularLinkedList::current);
		break;
	}
}

// update a value to a specific position in the backend in the step by step mode
void rUpdateSbs(short id, short pos, short val, wxStaticBitmap* arrow) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::setup(pos, val, 3);
		drawArrow(arrow, BstaticArray::current);
		break;

	case id_dynamic_array:
		++pos;
		BdynamicArray::setup(pos, val, 3);
		drawArrow(arrow, BdynamicArray::current);
		break;

	case id_simply_linked_list:
		++pos;
		BsimplyLinkedList::setup(pos, val, 3);
		drawArrow(arrow, BsimplyLinkedList::current);
		break;

	case id_doubly_linked_list:
		++pos;
		BdoublyLinkedList::setup(pos, val, 3);
		drawArrow(arrow, BdoublyLinkedList::current);
		break;

	case id_circular_linked_list:
		++pos;
		BcircularLinkedList::setup(pos, val, 3);
		drawArrow(arrow, BcircularLinkedList::current);
		break;
	}
}

// access to a specific position in the backend in the step by step mode
void rAccessSbs(short id, short pos, wxStaticBitmap* arrow) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::setup(pos, 0, 4);
		drawArrow(arrow, BstaticArray::current);
		break;

	case id_dynamic_array:
		++pos;
		BdynamicArray::setup(pos, 0, 4);
		drawArrow(arrow, BdynamicArray::current);
		break;


	case id_simply_linked_list:
		++pos;
		BsimplyLinkedList::setup(pos, 0, 4);
		drawArrow(arrow, BsimplyLinkedList::current);
		break;

	case id_doubly_linked_list:
		++pos;
		BdoublyLinkedList::setup(pos, 0, 4);
		drawArrow(arrow, BdoublyLinkedList::current);
		break;

	case id_circular_linked_list:
		++pos;
		BcircularLinkedList::setup(pos, 0, 4);
		drawArrow(arrow, BcircularLinkedList::current);
		break;
	}
}

// search a value in the backend in the step by step mode
void rSearchSbs(short id, short val, wxStaticBitmap* arrow) {
	switch (id) {
	case id_static_array:
		BstaticArray::setup(0, val, 5);
		drawArrow(arrow, BstaticArray::current);
		break;

	case id_dynamic_array:
		BdynamicArray::setup(0, val, 5);
		drawArrow(arrow, BdynamicArray::current);
		break;

	case id_simply_linked_list:
		BsimplyLinkedList::setup(0, val, 5);
		drawArrow(arrow, BsimplyLinkedList::current);
		break;

	case id_doubly_linked_list:
		BdoublyLinkedList::setup(0, val, 5);
		drawArrow(arrow, BdoublyLinkedList::current);
		break;

	case id_circular_linked_list:
		BcircularLinkedList::setup(0, val, 5);
		drawArrow(arrow, BcircularLinkedList::current);
		break;
	}
}

// return the current array size
short rBoxSize(short id) {
	switch (id) {
	case id_static_array:
		return BstaticArray::a_size;
		break;

	case id_dynamic_array:
		return BdynamicArray::a_size;
		break;

	case id_simply_linked_list:
		return BsimplyLinkedList::Size();
		break;

	case id_doubly_linked_list:
		return BdoublyLinkedList::Size();
		break;

	case id_circular_linked_list:
		return BcircularLinkedList::Size();
		break;

	case id_stack:
		return Bstack::Size();
		break;

	case id_queue:
		return Bqueue::Size();
		break;
	}

	return 0;
}

// return the value of the array
short rAtBox(short id, short pos) {
	switch (id) {
	case id_static_array:
		if (pos > BstaticArray::a_size) {
			return -1000;
		}

		return BstaticArray::a[pos];
		break;

	case id_dynamic_array:
		if (pos > BdynamicArray::a_size) {
			return -1000;
		}

		return BdynamicArray::a[pos];
		break;

	case id_simply_linked_list:
		if (pos > BsimplyLinkedList::a_size) {
			return -1000;
		}

		return BsimplyLinkedList::Value(pos);
		break;

	case id_doubly_linked_list:
		if (pos > BdoublyLinkedList::a_size) {
			return -1000;
		}

		return BdoublyLinkedList::Value(pos);
		break;

	case id_circular_linked_list:
		if (pos > BcircularLinkedList::a_size) {
			return -1000;
		}

		return BcircularLinkedList::Value(pos);
		break;

	case id_stack:
		if (pos > Bstack::a_size) {
			return -1000;
		}

		return Bstack::Value(pos);
		break;

	case id_queue:
		if (pos > Bqueue::a_size) {
			return -1000;
		}

		return Bqueue::Value(pos);
		break;
	}

	return -1000;
}

// return which is the current process during step by step mode
short rSbsMode(short id) {
	switch (id) {
	case id_static_array:
		return BstaticArray::mode;
		break;

	case id_dynamic_array:
		return BdynamicArray::mode;
		break;

	case id_simply_linked_list:
		return BsimplyLinkedList::mode;
		break;

	case id_doubly_linked_list:
		return BdoublyLinkedList::mode;
		break;

	case id_circular_linked_list:
		return BcircularLinkedList::mode;
		break;
	}

	return 0;
}
