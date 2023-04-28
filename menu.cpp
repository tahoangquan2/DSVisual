#include "main.h"
#include "menu.h"
#include <wx/wx.h>

menu::menu(wxPanel* parent) : wxPanel(parent) {
	bgm->SetSize(800, 800);
	bgm->SetBackgroundColour(wxColour(*wxBLUE));
	wxButton* button = new wxButton(bgm, 0, "Go front", wxPoint(100, 50), wxSize(200, 50));
	button->Bind(wxEVT_BUTTON, &menu::clicked, this);
}

void menu::clicked(wxCommandEvent& eve) {
	this->Hide();
	par->Show();
}