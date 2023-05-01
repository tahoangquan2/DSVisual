#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>

class UstaticArray : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent = nullptr;
	wxPanel* box[13];
	wxSpinCtrl* input_insert_pos = nullptr;
	wxSpinCtrl* input_insert_val = nullptr;
	wxSpinCtrl* input_delete_pos = nullptr;

	UstaticArray(wxPanel* parent);

	void showBox();

	void goBack(wxCommandEvent& e);
	void createRandom(wxCommandEvent& e);
	void importFile(wxCommandEvent& e);
	void exportFile(wxCommandEvent& e);
	void insertPosition(wxCommandEvent& e);
	void deletePosition(wxCommandEvent& e);
	void updatePosition(wxCommandEvent& e);
	void accessPosition(wxCommandEvent& e);
	void searchValue(wxCommandEvent& e);
};
