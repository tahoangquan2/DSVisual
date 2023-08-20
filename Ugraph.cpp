#include "Ugraph.h"
#include "receiver.h"

// main page for UI queue
Ugraph::Ugraph(wxPanel* parent) : wxPanel(parent) {
	//base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(this, wxID_ANY, "Go back", wxPoint(100, 100), wxSize(100, 25));

	button_back->Bind(wxEVT_BUTTON, &Ugraph::goBack, this);



	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	auto buttonPanel = createButtonPanel(this);

	canvas = new DrawingCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	canvas->Bind(CANVAS_RECT_ADDED, &Ugraph::OnRectAdded, this);
	canvas->Bind(CANVAS_RECT_REMOVED, &Ugraph::OnRectRemoved, this);

	rectCount = canvas->getObjectCount();

	sizer->Add(buttonPanel, 0, wxEXPAND | wxALL, 0);
	sizer->Add(canvas, 1, wxEXPAND | wxALL, 0);

	this->SetSizerAndFit(sizer);
}

void Ugraph::OnAddButtonClick(wxCommandEvent& event)
{
	std::uniform_int_distribution sizeDistrib(this->FromDIP(50), this->FromDIP(100));
	std::uniform_int_distribution xDistrib(0, canvas->GetSize().GetWidth());
	std::uniform_int_distribution yDistrib(0, canvas->GetSize().GetHeight());
	std::uniform_real_distribution angleDistrib(0.0, M_PI * 2.0);

	std::uniform_int_distribution colorDistrib(0, 0xFFFFFF);

	rectCount++;
	canvas->addRect(sizeDistrib(randomGen), sizeDistrib(randomGen), xDistrib(randomGen), yDistrib(randomGen),
		angleDistrib(randomGen), wxColour(colorDistrib(randomGen)), "Rect #" + std::to_string(rectCount));
}

void Ugraph::OnRemoveButtonClick(wxCommandEvent& event)
{
	canvas->removeTopRect();
}

void Ugraph::OnRectAdded(wxCommandEvent& event)
{

}

void Ugraph::OnRectRemoved(wxCommandEvent& event)
{

}

wxPanel* Ugraph::createButtonPanel(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent);
	wxButton* addRectButton = new wxButton(panel, wxID_ANY, "Add Rect");
	wxButton* removeLastButton = new wxButton(panel, wxID_ANY, "Remove Top");

	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(addRectButton, 0, wxEXPAND | wxALL, 3);
	sizer->Add(removeLastButton, 0, wxEXPAND | wxALL, 3);

	panel->SetSizer(sizer);

	addRectButton->Bind(wxEVT_BUTTON, &Ugraph::OnAddButtonClick, this);
	removeLastButton->Bind(wxEVT_BUTTON, &Ugraph::OnRemoveButtonClick, this);

	return panel;
}

// go back to menu
void Ugraph::goBack(wxCommandEvent& e) {
	rGoToPanel(this, parent);
}
