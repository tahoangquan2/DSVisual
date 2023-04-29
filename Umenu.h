#pragma once
#include <wx/wx.h>

class Umenu : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent_setting = nullptr;
	wxPanel* parent_static_array = nullptr;

	Umenu(wxPanel* parent);
	void toSetting(wxCommandEvent& e);
	void toStaticArray(wxCommandEvent& e);

};
