#pragma once
#include <wx/wx.h>

class UstaticArray : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent = nullptr;

	UstaticArray(wxPanel* parent);

	void goBack(wxCommandEvent& e);
	void createRandom(wxCommandEvent& e);
	void importFile(wxCommandEvent& e);
	void insertPosition(wxCommandEvent& e);
	void deletePosition(wxCommandEvent& e);
	void updatePosition(wxCommandEvent& e);
	void accessPosition(wxCommandEvent& e);
	void searchValue(wxCommandEvent& e);
};
