#include "receiver.h"
#include "BstaticArray.h"

void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel) {
	current_panel->Hide();
	goto_panel->Show();
}

void rClear(short id) {
	switch (id) {
	case 1:
		BstaticArray::addBox();
		break;
	}
}