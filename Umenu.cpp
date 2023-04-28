#include "receiver.h"
#include "Umain.h"
#include "Umenu.h"
#include <wx/wx.h>

Umenu::Umenu(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(1100, 700);

	wxButton* button_to_setting = new wxButton(base, wxID_ANY, "Setting", wxPoint(100, 50), wxSize(200, 50));

	button_to_setting->Bind(wxEVT_BUTTON, &Umenu::toSetting, this);
}

void Umenu::toSetting(wxCommandEvent& eve) {
	rGoToPanel(this, parent_setting);
}