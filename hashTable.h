#include "constant.h"

// UI for the hash table
class hashTable : public wxPanel {
public:
	wxPoint mouse_pos;
	wxPanel* parent = nullptr;
	wxChoice* button_size = nullptr;
	wxSpinCtrl* input_insert = nullptr;
	wxSpinCtrl* input_delete = nullptr;
	wxSpinCtrl* input_search = nullptr;
	wxButton* button_create_random = nullptr;
	wxButton* button_import_file = nullptr;
	wxButton* button_insert = nullptr;
	wxButton* button_sbs = nullptr;
	wxButton* button_sbs2 = nullptr;
	bool sbs_mode = false, during_sbs = false;
	wxButton* button_next = nullptr;
	wxButton* button_skip = nullptr;
	wxStaticText* text_insert = nullptr;
	short n, m, sz, x, y, z, inp;
	std::pair<short, short> V[30], E[100];
	short cv[30][3], ce[100][3], T[30], id, sbs_add_value;
	bool drag[30];

	hashTable(wxPanel* parent);

	void randomGraph(wxCommandEvent& e);
	void goBack(wxCommandEvent& e);
	void importFile(wxCommandEvent& e);
	void onLeftDown(wxMouseEvent& e);
	void onLeftUp(wxMouseEvent& e);
	void onMouseMove(wxMouseEvent& e);
	void onPaint(wxPaintEvent& e);
	void reDraw(wxCommandEvent& e);

	void resetColor();
	void addValue(wxCommandEvent& e);

	void sbsModeOn(wxCommandEvent& e);
	void sbsModeOff(wxCommandEvent& e);
	void nextStep(wxCommandEvent& e);
	void skipStep(wxCommandEvent& e);
};
