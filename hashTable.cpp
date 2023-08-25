#include "hashTable.h"
#include "receiver.h"

// main page for UI hash table
hashTable::hashTable(wxPanel* parent) : wxPanel(parent) {
	wxArrayString choices_size;
	choices_size.Add("Small");
	choices_size.Add("Medium");
	choices_size.Add("Big");

	wxButton* button_back = new wxButton(this, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	button_create_random = new wxButton(this, wxID_ANY, "Create Random", wxPoint(850, 60), wxSize(110, 45));
	button_import_file = new wxButton(this, wxID_ANY, "Import File", wxPoint(850, 120), wxSize(110, 45));
	button_insert = new wxButton(this, wxID_ANY, "Insert Value", wxPoint(850, 180), wxSize(110, 45));
	button_search = new wxButton(this, wxID_ANY, "Search Value", wxPoint(850, 290), wxSize(110, 45));
	button_delete = new wxButton(this, wxID_ANY, "Delete Value", wxPoint(850, 400), wxSize(110, 45));

	text_insert = new wxStaticText(this, wxID_ANY, "Value Insert:", wxPoint(850, 230));
	text_search = new wxStaticText(this, wxID_ANY, "Value Search:", wxPoint(850, 340));
	text_delete = new wxStaticText(this, wxID_ANY, "Value Delete:", wxPoint(850, 450));

	input_insert = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(850, 250), wxSize(110, 25), wxSP_WRAP, -999, 999);
	input_search = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(850, 360), wxSize(110, 25), wxSP_WRAP, -999, 999);
	input_delete = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(850, 470), wxSize(110, 25), wxSP_WRAP, -999, 999);

	button_size = new wxChoice(this, wxID_ANY, wxPoint(950, 600), wxSize(90, 60), choices_size);
	button_size->Select(0);

	button_sbs = new wxButton(this, wxID_ANY, "Step by Step", wxPoint(330, 10), wxSize(110, 45));
	button_sbs2 = new wxButton(this, wxID_ANY, "Back to Normal", wxPoint(330, 10), wxSize(110, 45));
	button_sbs2->Hide();
	button_next = new wxButton(this, wxID_ANY, "Next", wxPoint(460, 10), wxSize(110, 45));
	button_next->Hide();
	button_skip = new wxButton(this, wxID_ANY, "Skip", wxPoint(590, 10), wxSize(110, 45));
	button_skip->Hide();

	SetCursor(wxCursor(wxCURSOR_HAND));
	Bind(wxEVT_LEFT_DOWN, &hashTable::onLeftDown, this);
	Bind(wxEVT_LEFT_UP, &hashTable::onLeftUp, this);
	Bind(wxEVT_MOTION, &hashTable::onMouseMove, this);
	Bind(wxEVT_PAINT, &hashTable::onPaint, this);

	button_back->Bind(wxEVT_BUTTON, &hashTable::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &hashTable::randomGraph, this);
	button_import_file->Bind(wxEVT_BUTTON, &hashTable::importFile, this);
	button_insert->Bind(wxEVT_BUTTON, &hashTable::insertValue, this);
	button_search->Bind(wxEVT_BUTTON, &hashTable::searchValue, this);
	button_delete->Bind(wxEVT_BUTTON, &hashTable::deleteValue, this);
	button_size->Bind(wxEVT_CHOICE, &hashTable::reDraw, this);

	button_sbs->Bind(wxEVT_BUTTON, &hashTable::sbsModeOn, this);
	button_sbs2->Bind(wxEVT_BUTTON, &hashTable::sbsModeOff, this);
	button_next->Bind(wxEVT_BUTTON, &hashTable::nextStep, this);
	button_skip->Bind(wxEVT_BUTTON, &hashTable::skipStep, this);

	wxCommandEvent empty_e = wxCommandEvent();
	randomGraph(empty_e);
}

// go back to menu
void hashTable::goBack(wxCommandEvent& e) {
	wxCommandEvent empty_e = wxCommandEvent();
	randomGraph(empty_e);
	sbsModeOff(empty_e);
	rGoToPanel(this, parent);
}

// import the outside file
void hashTable::importFile(wxCommandEvent& e) {
	wxFileDialog open_file_dialog(this, _("Open File"), "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (open_file_dialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	wxString file_path = open_file_dialog.GetPath();
	std::ifstream file(file_path.ToStdString());

	if (file.is_open()) {
		int input_value[16], cnt = 0, line;
		while (file >> line) {
			int val = 0;
			++cnt;
			if (cnt >= 30) {
				showError("Number of values must be in range [1, 29]");
				return;
			}
			if (line < -999 || 999 < line) {
				showError("Value must be in range [-999, 999]");
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
void hashTable::randomGraph(wxCommandEvent& e) {
	resetColor();
	n = getRandom(3, 6);
	m = 0;
	for (short i = 1; i < 30; ++i) {
		T[i] = -1;
		V[i] = std::make_pair(getRandom(100, 700), getRandom(100, 500));
	}

	for (short i = 1; i <= n; ++i) {
		int x = getRandom(1, 999);
		input_insert->SetValue(x);
		wxCommandEvent empty_e = wxCommandEvent();
		insertValue(empty_e);
	}

	Refresh();
}

void hashTable::onLeftDown(wxMouseEvent& e) {
	for (short i = 1; i < 30; ++i) {
		wxRect insideRect(V[i].first - rad[sz], V[i].second - rad[sz], rad[sz] << 2, rad[sz] << 2);
		if (insideRect.Contains(e.GetPosition())) {
			drag[i] = true;
			break;
		}
	}
}

void hashTable::onLeftUp(wxMouseEvent& e) {
	for (short i = 1; i < 30; ++i) {
		drag[i] = false;
	}
}

void hashTable::onMouseMove(wxMouseEvent& e) {
	for (short i = 1; i < 30; ++i) {
		if (drag[i] == true) {
			mouse_pos = e.GetPosition();
			V[i].first = mouse_pos.x;
			V[i].second = mouse_pos.y;
			Refresh();
			break;
		}
	}
}

// draw hashTable
void hashTable::onPaint(wxPaintEvent& e) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	// draw edge
	for (short i = 1; i < 100; ++i) {
		if (T[E[i].first] == -1 || T[E[i].second] == -1) {
			continue;
		}

		dc.SetPen(wxPen(wxColour(ce[i][0], ce[i][1], ce[i][2]), 1));
		dc.DrawLine(wxPoint(V[E[i].first].first, V[E[i].first].second), wxPoint(V[E[i].second].first, V[E[i].second].second));
	}

	// draw vertex
	wxString text;
	for (short i = 1; i < 30; ++i) {
		if (T[i] == -1) {
			continue;
		}

		dc.SetPen(wxPen(wxColour(cv[i][0], cv[i][1], cv[i][2]), 2));
		dc.DrawRectangle(wxPoint(V[i].first - rad[sz], V[i].second - rad[sz]), wxSize(rad[sz] << 1, rad[sz] << 1));

		text = "";
		text << T[i];
		dc.DrawText(text, wxPoint(V[i].first - 4 - rad[sz] / 10, V[i].second - 6 - rad[sz] / 10));
	}
}

void hashTable::reDraw(wxCommandEvent& e) {
	sz = button_size->GetSelection();
	Refresh();
}

void hashTable::resetColor() {
	for (int i = 1; i < 30; ++i) {
		for (int j = 0; j < 3; ++j) {
			cv[i][j] = 0;
		}
	}
	for (int i = 1; i < 100; ++i) {
		for (int j = 0; j < 3; ++j) {
			ce[i][j] = 0;
		}
	}
}

void hashTable::insertValue(wxCommandEvent& e) {
	int val = input_insert->GetValue();
	inp = val;
	int modval = (val + 1000) % 100;

	if (sbs_mode == true && during_sbs == false) {
		id = 1;
		sbs_add_value = 0;
		during_sbs = true;
		button_create_random->Hide();
		button_import_file->Hide();
		button_insert->Hide();
		button_search->Hide();
		button_delete->Hide();
		text_insert->Hide();
		text_search->Hide();
		text_delete->Hide();
		input_insert->Hide();
		input_search->Hide();
		input_insert->Hide();
		return;
	}

	bool tf2 = false;
	for (int i = 1; i < 30; ++i) {
		if (T[i] == modval) {
			bool tf = false;
			for (int j = 1; j < 30; ++j) {
				if (T[j] == -1) {
					++m;
					E[m].first = i;
					E[m].second = j;
					T[j] = val;
					tf = tf2 = true;
					break;
				}
			}
			if (tf == false) {
				showError("No more than 29 elements");
				return;
			}
			else {
				break;
			}
		}
	}

	if (tf2 == false) {
		int u = 0, v = 0;
		for (int j = 1; j < 30; ++j) {
			if (T[j] == -1) {
				T[j] = modval;
				u = j;
				break;
			}
		}
		for (int j = 1; j < 30; ++j) {
			if (T[j] == -1) {
				T[j] = val;
				v = j;
				break;
			}
		}

		if (u != 0 && v != 0) {
			++m;
			E[m].first = u;
			E[m].second = v;
		}
		else {
			showError("No more than 29 elements");
			return;
		}
	}

	Refresh();
}

void hashTable::searchValue(wxCommandEvent& e) {
	resetColor();
	int val = input_search->GetValue();
	inp = val;

	if (sbs_mode == true && during_sbs == false) {
		id = 2;
		sbs_search = 0;
		during_sbs = true;
		button_create_random->Hide();
		button_import_file->Hide();
		button_insert->Hide();
		button_search->Hide();
		button_delete->Hide();
		text_insert->Hide();
		text_search->Hide();
		text_delete->Hide();
		input_insert->Hide();
		input_search->Hide();
		input_delete->Hide();
		return;
	}

	bool tf = false;
	if (val > 99) {
		tf = true;
	}

	for (int i = 1; i < 30; ++i) {
		if (T[i] == val) {
			if (tf == false) {
				tf = true;
				continue;
			}
			cv[i][0] = getRandom(0, 255);
			cv[i][1] = getRandom(0, 255);
			cv[i][2] = getRandom(0, 255);
			break;
		}
	}

	Refresh();
}

void hashTable::deleteValue(wxCommandEvent& e) {
	int val = input_search->GetValue();
	inp = val;

	if (sbs_mode == true && during_sbs == false) {
		id = 2;
		sbs_search = 0;
		during_sbs = true;
		button_create_random->Hide();
		button_import_file->Hide();
		button_insert->Hide();
		button_search->Hide();
		button_delete->Hide();
		text_insert->Hide();
		text_search->Hide();
		text_delete->Hide();
		input_insert->Hide();
		input_search->Hide();
		input_delete->Hide();
		return;
	}

	Refresh();
}

// turn on the step by step mode
void hashTable::sbsModeOn(wxCommandEvent& e) {
	sbs_mode = true;
	button_sbs->Hide();
	button_sbs2->Show();
	button_next->Show();
	button_skip->Show();

	resetColor();
	Refresh();
}

// turn off the step by step mode
void hashTable::sbsModeOff(wxCommandEvent& e) {
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
void hashTable::nextStep(wxCommandEvent& e) {
	if (during_sbs == false) {
		return;
	}

	resetColor();

	if (id == 1) {
		if (sbs_add_value == 0) {
			for (int i = 1; i < 30; ++i) {
				if (T[i] == inp % 100) {
					cv[i][0] = cv[i][1] = 0;
					cv[i][2] = 200;
					sbs_add_value = 1;
					break;
				}
			}
			if (sbs_add_value == 0) {
				wxCommandEvent empty_e = wxCommandEvent();
				insertValue(empty_e);
				for (int i = 29; 0 < i; --i) {
					if (T[i] == inp) {
						cv[i][0] = cv[i][1] = 0;
						cv[i][2] = 200;
						sbs_add_value = 2;
						break;
					}
				}
			}
		}
		else if (sbs_add_value == 1) {
			wxCommandEvent empty_e = wxCommandEvent();
			insertValue(empty_e);
			for (int i = 29; 0 < i; --i) {
				if (T[i] == inp) {
					cv[i][0] = cv[i][1] = 0;
					cv[i][2] = 200;
					sbs_add_value = 2;
					break;
				}
			}
		}
		else {
			during_sbs = false;
			resetColor();
		}
	}
	else if (id == 2) {
		if (sbs_search == 0) {
			for (int i = 1; i <= n; ++i) {
				if (T[i] == inp % 100) {
					cv[i][0] = cv[i][1] = 0;
					cv[i][2] = 200;
					sbs_search = i;
					break;
				}
			}
			if (sbs_search == 0) {
				during_sbs = false;
			}
		}
		else if (sbs_search != 69) {
			resetColor();
			for (int i = sbs_search + 1; i < 30; ++i) {
				if (T[i] == inp) {
					cv[i][0] = cv[i][1] = 0;
					cv[i][2] = 200;
					sbs_search = 69;
					break;
				}
			}
		}
		else {
			during_sbs = false;
			resetColor();
		}
	}

	if (during_sbs == false) {
		button_create_random->Show();
		button_import_file->Show();
		button_insert->Show();
		button_search->Show();
		button_delete->Show();
		text_insert->Show();
		text_search->Show();
		text_delete->Show();
		input_insert->Show();
		input_search->Show();
		input_delete->Show();
	}

	Refresh();
}

// skip all the steps in the step by step mode
void hashTable::skipStep(wxCommandEvent& e) {
	if (during_sbs == false) {
		return;
	}

	while (during_sbs == true) {
		wxCommandEvent empty_e = wxCommandEvent();
		nextStep(empty_e);
	}
}
