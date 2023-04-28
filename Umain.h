#pragma once
#include <wx/wx.h>

class Umain : public wxFrame {
public:
	wxPanel* base = new wxPanel(this);
public:
	Umain(const wxString& title);
};
