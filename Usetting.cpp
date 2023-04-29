#include "receiver.h"
#include "Umain.h"
#include "Usetting.h"
#include <wx/wx.h>

Usetting::Usetting(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(base, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));

	button_back->Bind(wxEVT_BUTTON, &Usetting::goBack, this);
}

void Usetting::goBack(wxCommandEvent& e) {
	rGoToPanel(this, parent);
}