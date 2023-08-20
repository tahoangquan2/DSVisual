#include "constant.h"

// UI for the graph
class graph : public wxPanel {

public:
	//wxPanel* base = new wxPanel(this);
	wxPanel* parent = nullptr;
	wxPoint m_Circle1Pos = wxPoint(100, 100), m_Circle2Pos = wxPoint(100, 100);
	wxPoint m_MousePos;
	bool m_IsDraggingCircle1 = false, m_IsDraggingCircle2 = false;

	graph(wxPanel* parent);

	void goBack(wxCommandEvent& e);
	void onLeftDown(wxMouseEvent& e);
	void onLeftUp(wxMouseEvent& e);
	void onMouseMove(wxMouseEvent& e);
	void onPaint(wxPaintEvent& e);
};
