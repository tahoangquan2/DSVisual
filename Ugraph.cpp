#include "Ugraph.h"
#include "receiver.h"

// main page for UI queue
Ugraph::Ugraph(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(base, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));

	button_back->Bind(wxEVT_BUTTON, &Ugraph::goBack, this);

	wxCommandEvent empty_e = wxCommandEvent();
}

// go back to menu
void Ugraph::goBack(wxCommandEvent& e) {
	rGoToPanel(this, parent);
}
