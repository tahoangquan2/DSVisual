#include "constant.h"

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
	wxButton* button_sbs = nullptr;
	wxButton* button_sbs2 = nullptr;
	bool sbs_mode = false;
	wxButton* button_next = nullptr;
	wxButton* button_skip = nullptr;
	wxStaticBitmap* arrow = nullptr;
	bool during_sbs = false;
	short fix_pos = 0;
	short fix_val = 0;

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
	void sbsModeOn(wxCommandEvent& e);
	void sbsModeOff(wxCommandEvent& e);
	void nextStep(wxCommandEvent& e);
	void skipStep(wxCommandEvent& e);

};
