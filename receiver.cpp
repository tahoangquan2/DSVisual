#include "receiver.h"
#include "UstaticArray.h"
#include "BstaticArray.h"
#include <time.h>

int getRandom(int l, int r) {
	return (rand() % (r - l + 1)) + l;
}

void drawBox(wxPanel** boxs, wxPanel* base, short pos, int value) {
	if (value == -1000) {
		boxs[pos]->Destroy();
		return;
	}
	boxs[pos] = new wxPanel(base, wxID_ANY, wxPoint(box_position[pos], box_y), wxSize(box_size, box_size), wxBORDER_DOUBLE);
	boxs[pos]->SetBackgroundColour(wxColour(box_color, box_color, box_color));
	wxString display_value;
	display_value << value;
	wxStaticText* test = new wxStaticText(boxs[pos], wxID_ANY, display_value);
	test->Center();
}

void showError(wxString message) {
	wxMessageBox(message, wxT("Error"), wxICON_ERROR);
}

void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel) {
	current_panel->Hide();
	goto_panel->Show();
}

void rClear(short id, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case id_static_array:
		for (int i = 1; i <= BstaticArray::a_size; ++i) {
			drawBox(boxs, base, i, -1000);
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
			BstaticArray::addBox(getRandom(-999, 999));
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