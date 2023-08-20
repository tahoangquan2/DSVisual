#include "constant.h"

// UI for the graph
class graph : public wxPanel {
public:
	wxPanel* parent = nullptr;
	wxPoint mouse_pos;
	short n, m;
	std::pair<short, short> V[16], E[50];
	short cv[3][16], ce[3][16], T[16], W[50];
	bool drag[16];

	graph(wxPanel* parent);

	void randomGraph();
	void goBack(wxCommandEvent& e);
	void onLeftDown(wxMouseEvent& e);
	void onLeftUp(wxMouseEvent& e);
	void onMouseMove(wxMouseEvent& e);
	void onPaint(wxPaintEvent& e);
};
