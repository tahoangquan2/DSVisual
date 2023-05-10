#include "Umenu.h"
#include "receiver.h"
#include "Umain.h"

// main page for the UI menu
Umenu::Umenu(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);

	wxButton* button_to_setting = new wxButton(base, wxID_ANY, "Setting", wxPoint(100, 50), wxSize(200, 50));
	wxButton* button_to_static_array = new wxButton(base, wxID_ANY, "Static Array", wxPoint(100, 100), wxSize(200, 50));

	button_to_setting->Bind(wxEVT_BUTTON, &Umenu::toSetting, this);
	button_to_static_array->Bind(wxEVT_BUTTON, &Umenu::toStaticArray, this);
}

// go to setting
void Umenu::toSetting(wxCommandEvent& e) {
	rGoToPanel(this, parent_setting);
}

// go to static array
void Umenu::toStaticArray(wxCommandEvent& e) {
	rGoToPanel(this, parent_static_array);
}