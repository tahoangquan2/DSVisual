#include "receiver.h"

#include "UstaticArray.h"

#include "BstaticArray.h"

wxStaticText* id_pos[13];

int getRandom(int l, int r) {
	return (rand() % (r - l + 1)) + l;
}

void showError(wxString message) {
	wxMessageBox(message, wxT("Error"), wxICON_ERROR);
}

void drawBox(wxPanel** boxs, wxPanel* base, short pos, short val = -1000) {
	if (pos > max_size) {
		return;
	}

	if (val == -1000) {
		wxString empty_space = " ";
		if (boxs[pos] != nullptr) {
			boxs[pos]->Destroy();
			boxs[pos] = nullptr;
		}
		if (id_pos[pos] != nullptr) {
			id_pos[pos]->Destroy();
			id_pos[pos] = nullptr;
		}
		return;
	}

	boxs[pos] = new wxPanel(base, wxID_ANY, wxPoint(box_position[pos], box_y), wxSize(box_size, box_size), wxBORDER_DOUBLE);
	boxs[pos]->SetBackgroundColour(wxColour(box_color, box_color, box_color));

	wxString display_value;
	display_value << val;
	wxStaticText* text = new wxStaticText(boxs[pos], wxID_ANY, display_value);
	text->Center();

	display_value = "";
	display_value << (pos - 1);
	id_pos[pos] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[pos] + 20, box_y + 60));
}

void drawArrow(wxStaticBitmap* arrow, short pos) {
	arrow->Show();
	arrow->SetPosition(wxPoint(box_position[pos] + 10, box_y - 50));
}

void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel) {
	current_panel->Hide();
	goto_panel->Show();
}

void rClear(short id, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case id_static_array:
		for (int i = 1; i <= BstaticArray::a_size; ++i) {
			BstaticArray::a[i] = 0;
			drawBox(boxs, base, i);
		}
		BstaticArray::a_size = 0;
		break;
	}
}

void rCreateRandom(short id, wxPanel** boxs, wxPanel* base) {
	srand(time(NULL));

	switch (id) {
	case id_static_array:
		short random_size = getRandom(3, 12);
		for (short i = 1; i <= random_size; ++i) {
			BstaticArray::addBox(getRandom(1, 69));
			drawBox(boxs, base, i, BstaticArray::a[i]);
		}
		break;
	}
}

void rStringToBox(short id, std::string& line, wxPanel** boxs, wxPanel* base) {
	int value[15] = {};
	short sz = 0;

	if (line.size() > 60) {
		showError("Input is too long");
		return;
	}

	for (int i = 0; i < line.size(); ++i) {
		if (line[i] == ',') {
			++sz;
			if (sz > 12) {
				break;
			}
		}
		else if ('0' <= line[i] && line[i] <= '9') {
			value[sz] = value[sz] * 10 + int(line[i]) - int('0');
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
	}
}

void rInsert(short id, short pos, short val, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::insertPosition(pos, val);
		for (short i = 1; i <= BstaticArray::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, BstaticArray::a[i]);
		}
	}
}

void rDelete(short id, short pos, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::deletePosition(pos);
		for (short i = 1; i <= BstaticArray::a_size; ++i) {
			drawBox(boxs, base, i);
			drawBox(boxs, base, i, BstaticArray::a[i]);
		}
	}
}

void rUpdate(short id, short pos, short val, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::a[pos] = val;
		drawBox(boxs, base, pos);
		drawBox(boxs, base, pos, BstaticArray::a[pos]);
	}
}

short rSearch(short id, short val) {
	switch (id) {
	case id_static_array:
		for (short i = 1; i <= BstaticArray::a_size; ++i) {
			if (BstaticArray::a[i] == val) {
				return i - 1;
			}
		}
		break;
	}
	return -1;
}

bool rNext(short id, wxPanel** boxs, wxPanel* base, wxStaticBitmap* arrow) {
	switch (id) {
	case id_static_array:
		if (BstaticArray::next() == true) {
			return true;
		}
		drawArrow(arrow, BstaticArray::current);
		drawBox(boxs, base, BstaticArray::current);
		drawBox(boxs, base, BstaticArray::current, BstaticArray::b[BstaticArray::current]);
		if (BstaticArray::current + 1 <= BstaticArray::b_size) {
			drawBox(boxs, base, BstaticArray::current + 1);
			drawBox(boxs, base, BstaticArray::current + 1, BstaticArray::b[BstaticArray::current + 1]);
		}
		break;
	}
}

void rInsertSbs(short id, short pos, short val, wxStaticBitmap* arrow) {
	switch (id) {
	case id_static_array:
		++pos;
		BstaticArray::setup(pos, val, 1);
		drawArrow(arrow, BstaticArray::current);
	}
}

int rBoxSize(short id) {
	switch (id) {
	case id_static_array:
		return BstaticArray::a_size;
		break;
	}
	return 0;
}

int rAtBox(short id, short pos) {
	switch (id) {
	case id_static_array:
		if (pos > BstaticArray::a_size) {
			return -1000;
		}
		return BstaticArray::a[pos];
		break;
	}
	return -1000;
}

short rSbsMode(short id) {
	switch (id) {
	case id_static_array:
		return BstaticArray::mode;
		break;
	}
	return 0;
}