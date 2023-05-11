#include "constant.h"

// UI for the static array
class UstaticArray : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent = nullptr;
	wxPanel* box[13];
	wxSpinCtrl* input_insert_pos = nullptr;
	wxSpinCtrl* input_insert_val = nullptr;
	wxSpinCtrl* input_delete_pos = nullptr;
	wxSpinCtrl* input_update_pos = nullptr;
	wxSpinCtrl* input_update_val = nullptr;
	wxSpinCtrl* input_access_pos = nullptr;
	wxStaticText* output_access_val = nullptr;
	wxSpinCtrl* input_search_val = nullptr;
	wxStaticText* output_search_pos = nullptr;
	wxStaticText* id_pos[15];

	UstaticArray(wxPanel* parent);

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
