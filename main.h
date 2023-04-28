#pragma once
#include <wx/wx.h>

class main : public wxFrame {
public:
	wxPanel* bg = new wxPanel(this);
public:
	main(const wxString& title);
private:
	void clicked(wxCommandEvent& eve);
};
