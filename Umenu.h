#pragma once
#include <wx/wx.h>

class Umenu : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent_setting = nullptr;

	Umenu(wxPanel* parent);

private:
	void toSetting(wxCommandEvent& eve);

};
