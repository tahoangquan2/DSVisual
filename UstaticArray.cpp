#include "receiver.h"
#include "UstaticArray.h"
#include <wx/wx.h>

UstaticArray::UstaticArray(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(base, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	wxButton* button_create_random = new wxButton(base, wxID_ANY, "Create Random", wxPoint(70, 570), wxSize(110, 45));
	wxPanel* box[13];

	for (int i = 1; i <= max_size; ++i) {
		box[i] = new wxPanel(base, wxID_ANY, wxPoint(box_position[i], box_y), wxSize(box_size, box_size), wxBORDER_DOUBLE);
	}

	button_back->Bind(wxEVT_BUTTON, &UstaticArray::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &UstaticArray::createRandom, this);
}

void UstaticArray::goBack(wxCommandEvent& e) {
	rGoToPanel(this, parent);
}

void UstaticArray::createRandom(wxCommandEvent& e) {
	rClear(id_static_array);
	rCreateRandom(id_static_array);
}
