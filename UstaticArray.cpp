#include "receiver.h"
#include "UstaticArray.h"
#include <wx/wx.h>

UstaticArray::UstaticArray(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(base, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	wxButton* button_create_random = new wxButton(base, wxID_ANY, "Create Random", wxPoint(70, 570), wxSize(110, 45));

	button_back->Bind(wxEVT_BUTTON, &UstaticArray::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &UstaticArray::createRandom, this);
}

void UstaticArray::goBack(wxCommandEvent& e) {
	rGoToPanel(this, parent);
	rClear(id_static_array, box, base);
	rCreateRandom(id_static_array, box, base);
}

void UstaticArray::createRandom(wxCommandEvent& e) {
	rClear(id_static_array, box, base);
	rCreateRandom(id_static_array, box, base);
}
