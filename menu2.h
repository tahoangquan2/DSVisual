#pragma once
#include <wx/wx.h>

class menu2 : public wxPanel {
public:
	wxPanel* bgn = new wxPanel(this);
	wxPanel* par = nullptr;
public:
	menu2(wxPanel* parent);
private:
	void clicked(wxCommandEvent& eve);
};
