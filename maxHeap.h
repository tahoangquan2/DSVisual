#include "constant.h"

// UI for the hash table
class maxHeap : public wxPanel {
public:
	wxPoint mouse_pos;
	wxPanel* parent = nullptr;
	wxChoice* button_size = nullptr;
	wxChoice* button_style = nullptr;
	wxSpinCtrl* input_insert = nullptr;
	wxButton* button_create_random = nullptr;
	wxButton* button_import_file = nullptr;
	wxButton* button_insert = nullptr;
	wxButton* button_search = nullptr;
	wxButton* button_delete = nullptr;
	wxButton* button_sbs = nullptr;
	wxButton* button_sbs2 = nullptr;
	bool sbs_mode = false, during_sbs = false;
	wxButton* button_next = nullptr;
	wxButton* button_skip = nullptr;
	wxStaticText* text_insert = nullptr;
	wxStaticText* text_search = nullptr;
	short n, m, style, sz, x, y, z, inp;
	std::pair<short, short> V[35];
	short cv[35][3], ce[35][3], a[35], id, goc[35];
	bool drag[35];
	short sbs_insert, sbs_delete;

	maxHeap(wxPanel* parent);

	void randomGraph(wxCommandEvent& e);
	void goBack(wxCommandEvent& e);
	void importFile(wxCommandEvent& e);
	void onLeftDown(wxMouseEvent& e);
	void onLeftUp(wxMouseEvent& e);
	void onMouseMove(wxMouseEvent& e);
	void onPaint(wxPaintEvent& e);
	void reDraw(wxCommandEvent& e);

	void resetColor();
	void insertValue(wxCommandEvent& e);
	void searchValue(wxCommandEvent& e);
	void deleteValue(wxCommandEvent& e);
	void doHeap1();
	void doHeap2();

	void sbsModeOn(wxCommandEvent& e);
	void sbsModeOff(wxCommandEvent& e);
	void nextStep(wxCommandEvent& e);
	void skipStep(wxCommandEvent& e);
};
