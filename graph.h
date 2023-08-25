#include "constant.h"

// UI for the graph
class graph : public wxPanel {
public:
	wxPanel* parent = nullptr;
	wxPoint mouse_pos;
	wxChoice* button_style;
	wxChoice* button_size;
	short n, m, style, sz, x, y, z;
	std::pair<short, short> V[16], E[50];
	short cv[16][3], ce[16][3];
	int W[50];
	bool drag[16], vis[16];

	graph(wxPanel* parent);

	void randomGraph(wxCommandEvent& e);
	void goBack(wxCommandEvent& e);
	void importFile(wxCommandEvent& e);
	void onLeftDown(wxMouseEvent& e);
	void onLeftUp(wxMouseEvent& e);
	void onMouseMove(wxMouseEvent& e);
	void onPaint(wxPaintEvent& e);
	void reDraw(wxCommandEvent& e);

	void findCC(wxCommandEvent& e);
	void dfsCC(short u);

};
