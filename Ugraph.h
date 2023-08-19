#include "constant.h"

// UI for the stack
class Ugraph : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent = nullptr;

	Ugraph(wxPanel* parent);

	void goBack(wxCommandEvent& e);

};
