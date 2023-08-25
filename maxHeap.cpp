#include "maxHeap.h"
#include "receiver.h"

// main page for UI hash table
maxHeap::maxHeap(wxPanel* parent) : wxPanel(parent) {
	wxArrayString choices_style;
	choices_style.Add("Circle");
	choices_style.Add("Square");

	wxArrayString choices_size;
	choices_size.Add("Small");
	choices_size.Add("Medium");
	choices_size.Add("Big");

	wxButton* button_back = new wxButton(this, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	button_create_random = new wxButton(this, wxID_ANY, "Create Random", wxPoint(850, 60), wxSize(110, 45));
	button_import_file = new wxButton(this, wxID_ANY, "Import File", wxPoint(850, 120), wxSize(110, 45));
	button_insert = new wxButton(this, wxID_ANY, "Insert Value", wxPoint(850, 180), wxSize(110, 45));
	button_search = new wxButton(this, wxID_ANY, "Get Size", wxPoint(850, 290), wxSize(110, 45));
	button_delete = new wxButton(this, wxID_ANY, "Delete Value", wxPoint(850, 400), wxSize(110, 45));

	text_insert = new wxStaticText(this, wxID_ANY, "Value Insert:", wxPoint(850, 230));

	input_insert = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(850, 250), wxSize(110, 25), wxSP_WRAP, 1, 999);

	button_style = new wxChoice(this, wxID_ANY, wxPoint(850, 600), wxSize(90, 60), choices_style);
	button_size = new wxChoice(this, wxID_ANY, wxPoint(950, 600), wxSize(90, 60), choices_size);
	button_style->Select(0);
	button_size->Select(0);

	button_sbs = new wxButton(this, wxID_ANY, "Step by Step", wxPoint(330, 10), wxSize(110, 45));
	button_sbs2 = new wxButton(this, wxID_ANY, "Back to Normal", wxPoint(330, 10), wxSize(110, 45));
	button_sbs2->Hide();
	button_next = new wxButton(this, wxID_ANY, "Next", wxPoint(460, 10), wxSize(110, 45));
	button_next->Hide();
	button_skip = new wxButton(this, wxID_ANY, "Skip", wxPoint(590, 10), wxSize(110, 45));
	button_skip->Hide();

	SetCursor(wxCursor(wxCURSOR_HAND));
	Bind(wxEVT_LEFT_DOWN, &maxHeap::onLeftDown, this);
	Bind(wxEVT_LEFT_UP, &maxHeap::onLeftUp, this);
	Bind(wxEVT_MOTION, &maxHeap::onMouseMove, this);
	Bind(wxEVT_PAINT, &maxHeap::onPaint, this);

	button_back->Bind(wxEVT_BUTTON, &maxHeap::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &maxHeap::randomGraph, this);
	button_import_file->Bind(wxEVT_BUTTON, &maxHeap::importFile, this);
	button_insert->Bind(wxEVT_BUTTON, &maxHeap::insertValue, this);
	button_search->Bind(wxEVT_BUTTON, &maxHeap::searchValue, this);
	button_delete->Bind(wxEVT_BUTTON, &maxHeap::deleteValue, this);
	button_size->Bind(wxEVT_CHOICE, &maxHeap::reDraw, this);
	button_style->Bind(wxEVT_CHOICE, &maxHeap::reDraw, this);

	button_sbs->Bind(wxEVT_BUTTON, &maxHeap::sbsModeOn, this);
	button_sbs2->Bind(wxEVT_BUTTON, &maxHeap::sbsModeOff, this);
	button_next->Bind(wxEVT_BUTTON, &maxHeap::nextStep, this);
	button_skip->Bind(wxEVT_BUTTON, &maxHeap::skipStep, this);

	wxCommandEvent empty_e = wxCommandEvent();
	randomGraph(empty_e);
}

// go back to menu
void maxHeap::goBack(wxCommandEvent& e) {
	wxCommandEvent empty_e = wxCommandEvent();
	randomGraph(empty_e);
	sbsModeOff(empty_e);
	rGoToPanel(this, parent);
}

// import the outside file
void maxHeap::importFile(wxCommandEvent& e) {
	wxFileDialog open_file_dialog(this, _("Open File"), "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (open_file_dialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	wxString file_path = open_file_dialog.GetPath();
	std::ifstream file(file_path.ToStdString());

	if (file.is_open()) {
		int input_value[35], cnt = 0, line;
		while (file >> line) {
			int val = 0;
			++cnt;
			if (cnt >= 15) {
				showError("Number of values must be in range [1, 15]");
				return;
			}
			if (line < 1 || 999 < line) {
				showError("Value must be in range [1, 999]");
				return;
			}
			input_value[cnt] = val;
		}
		file.close();

		m = 0;
		for (short i = 1; i <= cnt; ++i) {
			input_insert->SetValue(input_value[i]);
			wxCommandEvent empty_e = wxCommandEvent();
			insertValue(empty_e);
		}

		Refresh();
	}
	else {
		showError("Cannot open file");
	}
}

// create a random hash table
void maxHeap::randomGraph(wxCommandEvent& e) {
	resetColor();
	m = getRandom(3, 10);
	for (short i = 1; i <= 15; ++i) {
		V[i] = std::make_pair(getRandom(100, 700), getRandom(100, 500));
		a[i] = a[i << 1] = a[i << 1 | 1] = -1;
	}

	for (short i = 1; i <= m; ++i) {
		int x = getRandom(1, 999);
		input_insert->SetValue(x);
		wxCommandEvent empty_e = wxCommandEvent();
		insertValue(empty_e);
	}
	goc[1] = 1;

	Refresh();
}

void maxHeap::onLeftDown(wxMouseEvent& e) {
	for (short i = 1; i <= n; ++i) {
		wxRect insideRect(V[i].first - rad[sz], V[i].second - rad[sz], rad[sz] << 2, rad[sz] << 2);
		if (insideRect.Contains(e.GetPosition())) {
			drag[i] = true;
			break;
		}
	}
}

void maxHeap::onLeftUp(wxMouseEvent& e) {
	for (short i = 1; i <= n; ++i) {
		drag[i] = false;
	}
}

void maxHeap::onMouseMove(wxMouseEvent& e) {
	for (short i = 1; i <= n; ++i) {
		if (drag[i] == true) {
			mouse_pos = e.GetPosition();
			V[i].first = mouse_pos.x;
			V[i].second = mouse_pos.y;
			Refresh();
			break;
		}
	}
}

// draw maxHeap
void maxHeap::onPaint(wxPaintEvent& e) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	// draw edge
	for (short i = 1; i <= n; ++i) {
		for (short j = (i << 1); j <= (i << 1 | 1); ++j) {
			if (a[i] == -1 || a[j] == -1) {
				continue;
			}
			dc.SetPen(wxPen(wxColour(0, 0, 0), 1));
			dc.DrawLine(wxPoint(V[i].first, V[i].second), wxPoint(V[j].first, V[j].second));
		}
	}

	// draw vertex
	wxString text;
	for (short i = 1; i <= n; ++i) {
		if (a[i] == -1) {
			continue;
		}

		dc.SetPen(wxPen(wxColour(cv[i][0], cv[i][1], cv[i][2]), B[goc[i]]));

		if (style == 0) {
			dc.DrawCircle(wxPoint(V[i].first, V[i].second), rad[sz]);
		}
		else {
			dc.DrawRectangle(wxPoint(V[i].first - rad[sz], V[i].second - rad[sz]), wxSize(rad[sz] << 1, rad[sz] << 1));
		}

		text = "";
		text << int(a[i]);
		dc.DrawText(text, wxPoint(V[i].first - 4 - rad[sz] / 10, V[i].second - 6 - rad[sz] / 10));
	}
}

void maxHeap::reDraw(wxCommandEvent& e) {
	sz = button_size->GetSelection();
	style = button_style->GetSelection();
	Refresh();
}

void maxHeap::resetColor() {
	for (int i = 1; i < 30; ++i) {
		for (int j = 0; j < 3; ++j) {
			cv[i][j] = 0;
		}
	}
	for (int i = 1; i < 30; ++i) {
		for (int j = 0; j < 3; ++j) {
			ce[i][j] = 0;
		}
	}
}

void maxHeap::doHeap1() {
	for (int i = n; i > 1; i >>= 1) {
		if (a[i >> 1] < a[i]) {
			std::swap(a[i >> 1], a[i]);
		}
	}
}

void maxHeap::doHeap2() {
	for (int i = 1; 0 <= i; i += 0) {
		if (a[i << 1] == -1 && a[i << 1 | 1] == -1) {
			break;
		}
		else if (a[i << 1] == -1 && a[i << 1 | 1] != -1) {
			if (a[i << 1 | 1] > a[i]) {
				std::swap(a[i << 1 | 1], a[i]);
				i = i << 1 | 1;
			}
			else {
				break;
			}
		}
		else if (a[i << 1] != -1 && a[i << 1 | 1] == -1) {
			if (a[i << 1] > a[i]) {
				std::swap(a[i << 1], a[i]);
				i = i << 1;
			}
			else {
				break;
			}
		}
		else {
			if (a[i << 1] >= a[i << 1 | 1]) {
				std::swap(a[i << 1], a[i]);
				i = i << 1;
			}
			else {
				std::swap(a[i << 1 | 1], a[i]);
				i = i << 1 | 1;
			}
		}
	}
}

void maxHeap::insertValue(wxCommandEvent& e) {
	resetColor();
	inp = input_insert->GetValue();

	if (sbs_mode == true && during_sbs == false) {
		id = 1;
		sbs_insert = 0;
		during_sbs = true;
		button_create_random->Hide();
		button_import_file->Hide();
		button_insert->Hide();
		button_search->Hide();
		button_delete->Hide();
		text_insert->Hide();
		text_search->Hide();
		input_insert->Hide();
		return;
	}

	++n;
	a[n] = inp;
	doHeap1();

	Refresh();
}

void maxHeap::searchValue(wxCommandEvent& e) {
	resetColor();

	wxString tt = "";
	tt << "The size is " << n;
	showError(tt);

	Refresh();
}

void maxHeap::deleteValue(wxCommandEvent& e) {
	resetColor();

	if (sbs_mode == true && during_sbs == false) {
		id = 2;
		sbs_delete = 0;
		during_sbs = true;
		button_create_random->Hide();
		button_import_file->Hide();
		button_insert->Hide();
		button_search->Hide();
		button_delete->Hide();
		text_insert->Hide();
		text_search->Hide();
		input_insert->Hide();
		return;
	}

	a[1] = a[n];
	a[n] = -1;
	--n;
	doHeap2();

	Refresh();
}

// turn on the step by step mode
void maxHeap::sbsModeOn(wxCommandEvent& e) {
	//sbs_mode = true;
	//button_sbs->Hide();
	//button_sbs2->Show();
	//button_next->Show();
	//button_skip->Show();

	//resetColor();
	//Refresh();
}

// turn off the step by step mode
void maxHeap::sbsModeOff(wxCommandEvent& e) {
	wxCommandEvent empty_e = wxCommandEvent();
	skipStep(empty_e);

	sbs_mode = during_sbs = false;
	button_sbs2->Hide();
	button_sbs->Show();
	button_next->Hide();
	button_skip->Hide();

	resetColor();
	Refresh();
}

// go to the next step in the step by step mode
void maxHeap::nextStep(wxCommandEvent& e) {
	if (during_sbs == false) {
		return;
	}

	resetColor();
	if (id == 1) {
		wxCommandEvent empty_e = wxCommandEvent();
		insertValue(empty_e);
	}
	else {
		wxCommandEvent empty_e = wxCommandEvent();
		deleteValue(empty_e);
	}

	if (during_sbs == false) {
		button_create_random->Show();
		button_import_file->Show();
		button_insert->Show();
		button_search->Show();
		button_delete->Show();
		text_insert->Show();
		text_search->Show();
		input_insert->Show();
	}

	Refresh();
}

// skip all the steps in the step by step mode
void maxHeap::skipStep(wxCommandEvent& e) {
	if (during_sbs == false) {
		return;
	}

	while (during_sbs == true) {
		wxCommandEvent empty_e = wxCommandEvent();
		nextStep(empty_e);
	}
}
