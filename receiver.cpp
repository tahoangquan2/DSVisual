#include "receiver.h"

void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel) {
	current_panel->Hide();
	goto_panel->Show();
}