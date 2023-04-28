#include "main.h"
#include "menu2.h"
#include <wx/wx.h>

menu2::menu2(wxPanel* parent) : wxPanel(parent) {
	bgn->SetSize(800, 800);
	bgn->SetBackgroundColour(wxColour(*wxRED));
	wxButton* button = new wxButton(bgn, 0, "Go back", wxPoint(100, 150), wxSize(200, 50));
	button->Bind(wxEVT_BUTTON, &menu2::clicked, this);
}

void menu2::clicked(wxCommandEvent& eve) {
	this->Hide();
	par->Show();
}