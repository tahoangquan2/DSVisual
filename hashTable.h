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
	short n, m, sz, x, y, z;
	std::pair<short, short> V[30], E[100];
	short cv[30][3], ce[100][3], T[30];
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
};
