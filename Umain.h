#pragma once
#include <wx/wx.h>

class Umain : public wxFrame {

public:
	wxPanel* base = new wxPanel(this);
	Umain(const wxString& title);

};
