#pragma once
#include <wx/wx.h>

class Usetting : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent = nullptr;

	Usetting(wxPanel* parent);

	void goBack(wxCommandEvent& e);

};
