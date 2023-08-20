#include "constant.h"

#include <wx/wx.h>
#include <wx/listbook.h>
#include <random>
#include "drawingcanvas.h"
#include <wx/statusbr.h>

// UI for the stack
class Ugraph : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent = nullptr;

	Ugraph(wxPanel* parent);

	void goBack(wxCommandEvent& e);

	void OnAddButtonClick(wxCommandEvent& event);
	void OnRemoveButtonClick(wxCommandEvent& event);

	void OnRectAdded(wxCommandEvent& event);
	void OnRectRemoved(wxCommandEvent& event);

	wxPanel* createButtonPanel(wxWindow* parent);

	DrawingCanvas* canvas;

	int rectCount = 0;
	std::mt19937 randomGen;
};
