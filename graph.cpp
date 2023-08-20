#include "graph.h"
#include "receiver.h"

// main page for UI queue
graph::graph(wxPanel* parent) : wxPanel(parent) {
	//base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(this, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	SetCursor(wxCursor(wxCURSOR_HAND));

	Bind(wxEVT_LEFT_DOWN, &graph::onLeftDown, this);
	Bind(wxEVT_LEFT_UP, &graph::onLeftUp, this);
	Bind(wxEVT_MOTION, &graph::onMouseMove, this);
	Bind(wxEVT_PAINT, &graph::onPaint, this);

	button_back->Bind(wxEVT_BUTTON, &graph::goBack, this);
}

// go back to menu
void graph::goBack(wxCommandEvent& e) {
	rGoToPanel(this, parent);
}

void graph::onLeftDown(wxMouseEvent& e)
{
	wxRect circle1Rect(m_Circle1Pos.x - 10, m_Circle1Pos.y - 10, 20, 20);
	wxRect circle2Rect(m_Circle2Pos.x - 10, m_Circle2Pos.y - 10, 20, 20);

	if (circle1Rect.Contains(e.GetPosition()))
		m_IsDraggingCircle1 = true;
	else if (circle2Rect.Contains(e.GetPosition()))
		m_IsDraggingCircle2 = true;
}

void graph::onLeftUp(wxMouseEvent& e)
{
	m_IsDraggingCircle1 = false;
	m_IsDraggingCircle2 = false;
}

void graph::onMouseMove(wxMouseEvent& e) {
	if (m_IsDraggingCircle1 == true || m_IsDraggingCircle2 == true) {
		m_MousePos = e.GetPosition();

		if (m_IsDraggingCircle1) {
			m_Circle1Pos = m_MousePos;
		}
		else if (m_IsDraggingCircle2) {
			m_Circle2Pos = m_MousePos;
		}

		Refresh();
	}
}

void graph::onPaint(wxPaintEvent& e)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	dc.SetPen(wxPen(*wxBLACK, 1));

	wxCoord x1 = m_Circle1Pos.x, y1 = m_Circle1Pos.y, x2 = m_Circle2Pos.x, y2 = m_Circle2Pos.y;
	dc.DrawLine(x1, y1, x2, y2);
	dc.DrawCircle(x1, y1, 20);
	dc.DrawCircle(x2, y2, 20);
}
