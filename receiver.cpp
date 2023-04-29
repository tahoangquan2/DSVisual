#include "receiver.h"
#include "UstaticArray.h"
#include "BstaticArray.h"
#include <time.h>

int getRandom(int l, int r) {
	return (rand() % (r - l + 1)) + l;
}

void drawBox(wxPanel** boxs, wxPanel* base, int pos, int value) {
	if (value == -1000) {
		boxs[pos]->Destroy();
		return;
	}
	boxs[pos] = new wxPanel(base, wxID_ANY, wxPoint(box_position[pos], box_y), wxSize(box_size, box_size), wxBORDER_DOUBLE);
	boxs[pos]->SetBackgroundColour(wxColour(box_color, box_color, box_color));
	wxString tmp;
	tmp << value;
	wxStaticText* test = new wxStaticText(boxs[pos], wxID_ANY, tmp);
	test->Center();
}

void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel) {
	current_panel->Hide();
	goto_panel->Show();
}

void rClear(short id, wxPanel** boxs, wxPanel* base) {
	switch (id) {
	case 1:
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
	case 1:
		short random_size = getRandom(3, 12);
		for (int i = 1; i <= random_size; ++i) {
			BstaticArray::addBox(getRandom(-999, 999));
			drawBox(boxs, base, i, BstaticArray::a[i]);
		}
		break;
	}
}
