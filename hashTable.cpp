#include "hashTable.h"
#include "receiver.h"

// main page for UI hash table
hashTable::hashTable(wxPanel* parent) : wxPanel(parent) {
	wxArrayString choices_size;
	choices_size.Add("Small");
	choices_size.Add("Medium");
	choices_size.Add("Big");

	wxButton* button_back = new wxButton(this, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	wxButton* button_create_random = new wxButton(this, wxID_ANY, "Create Random", wxPoint(850, 60), wxSize(110, 45));
	wxButton* button_import_file = new wxButton(this, wxID_ANY, "Import File", wxPoint(850, 120), wxSize(110, 45));
	wxButton* button_insert = new wxButton(this, wxID_ANY, "Add Value", wxPoint(850, 180), wxSize(110, 45));

	wxStaticText* text_insert = new wxStaticText(this, wxID_ANY, "Value:", wxPoint(850, 230));

	input_insert = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(850, 250), wxSize(110, 25), wxSP_WRAP, -999, 999);

	button_size = new wxChoice(this, wxID_ANY, wxPoint(950, 600), wxSize(90, 60), choices_size);
	button_size->Select(0);

	SetCursor(wxCursor(wxCURSOR_HAND));

	Bind(wxEVT_LEFT_DOWN, &hashTable::onLeftDown, this);
	Bind(wxEVT_LEFT_UP, &hashTable::onLeftUp, this);
	Bind(wxEVT_MOTION, &hashTable::onMouseMove, this);
	Bind(wxEVT_PAINT, &hashTable::onPaint, this);

	button_back->Bind(wxEVT_BUTTON, &hashTable::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &hashTable::randomGraph, this);
	button_import_file->Bind(wxEVT_BUTTON, &hashTable::importFile, this);
	button_insert->Bind(wxEVT_BUTTON, &hashTable::addValue, this);
	button_size->Bind(wxEVT_CHOICE, &hashTable::reDraw, this);

	wxCommandEvent empty_e = wxCommandEvent();
	randomGraph(empty_e);
}

// go back to menu
void hashTable::goBack(wxCommandEvent& e) {
	wxCommandEvent empty_e = wxCommandEvent();
	randomGraph(empty_e);
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
			addValue(empty_e);
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
		addValue(empty_e);
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

void hashTable::addValue(wxCommandEvent& e) {
	int val = input_insert->GetValue();
	int modval = (val + 1000) % 100;

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