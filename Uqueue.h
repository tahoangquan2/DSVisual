#include "constant.h"

// UI for the stack
class Uqueue : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent = nullptr;
	wxPanel* box[13];
	wxSpinCtrl* input_insert_val = nullptr;
	short input_insert_pos = 0;
	short input_delete_pos = 0;
	wxButton* button_sbs = nullptr;
	wxButton* button_sbs2 = nullptr;
	bool sbs_mode = false;
	wxStaticBitmap* arrow = nullptr;
	short fix_pos = 0;
	short fix_val = 0;
	wxStaticText* id_pos[15];
	wxStaticBitmap* arrow2[15];

	Uqueue(wxPanel* parent);

	void goBack(wxCommandEvent& e);
	void createRandom(wxCommandEvent& e);
	void importFile(wxCommandEvent& e);
	void exportFile(wxCommandEvent& e);
	void insertPosition(wxCommandEvent& e);
	void deletePosition(wxCommandEvent& e);
	void insertValue(wxCommandEvent& e);
	void insertValue2(wxCommandEvent& e);
	void popBack(wxCommandEvent& e);
	void popFront(wxCommandEvent& e);
	void clearQueue(wxCommandEvent& e);

};
