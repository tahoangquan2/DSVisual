#pragma once
#include <wx/wx.h>

class menu : public wxPanel {
public:
	wxPanel* bgm = new wxPanel(this);
	wxPanel* par = nullptr;
public:
	menu(wxPanel* parent);
private:
	void clicked(wxCommandEvent& eve);
};
