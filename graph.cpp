#include "graph.h"
#include "receiver.h"
#include <wx/event.h>

// main page for UI queue
graph::graph(wxPanel* parent) : wxPanel(parent) {
	wxArrayString choices_style;
	choices_style.Add("Circle");
	choices_style.Add("Square");

	wxArrayString choices_size;
	choices_size.Add("Small");
	choices_size.Add("Medium");
	choices_size.Add("Big");

	wxButton* button_back = new wxButton(this, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	wxButton* button_import_file = new wxButton(this, wxID_ANY, "Import File", wxPoint(200, 570), wxSize(110, 45));

	button_style = new wxChoice(this, wxID_ANY, wxPoint(850, 600), wxSize(90, 60), choices_style);
	button_size = new wxChoice(this, wxID_ANY, wxPoint(950, 600), wxSize(90, 60), choices_size);

	button_style->Select(0);
	button_size->Select(0);

	SetCursor(wxCursor(wxCURSOR_HAND));

	Bind(wxEVT_LEFT_DOWN, &graph::onLeftDown, this);
	Bind(wxEVT_LEFT_UP, &graph::onLeftUp, this);
	Bind(wxEVT_MOTION, &graph::onMouseMove, this);
	Bind(wxEVT_PAINT, &graph::onPaint, this);

	button_back->Bind(wxEVT_BUTTON, &graph::goBack, this);
	button_import_file->Bind(wxEVT_BUTTON, &graph::importFile, this);
	button_style->Bind(wxEVT_CHOICE, &graph::reDraw, this);
	button_size->Bind(wxEVT_CHOICE, &graph::reDraw, this);

	randomGraph();
}

// go back to menu
void graph::goBack(wxCommandEvent& e) {
	randomGraph();
	rGoToPanel(this, parent);
}

// import the outside file
void graph::importFile(wxCommandEvent& e) {
	wxFileDialog open_file_dialog(this, _("Open File"), "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (open_file_dialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	wxString file_path = open_file_dialog.GetPath();
	std::ifstream file(file_path.ToStdString());

	if (file.is_open()) {
		int input_value[50][3], cnt_m = 0;
		std::string line;
		while (std::getline(file, line)) {
			int v[3] = {0, 0, 0}, cnt = 0;
			for (short i = 0; i < line.size(); ++i) {
				if ('0' <= line[i] && line[i] <= '9') {
					v[cnt] = v[cnt] * 10 + int(line[i]) - int('0');
					if (cnt <= 1 && (v[cnt] < 1 || v[cnt] > 15)) {
						showError("Value must be in range [1, 15]");
						return;
					}
					else if (cnt == 2 && (v[cnt] < 0 || v[cnt] > 100000000)) {
						showError("Value must be in range [0, 100000000]");
						return;
					}
				}
				else {
					++cnt;
					if (cnt > 2) {
						break;
					}
				}
			}
			++cnt_m;
			if (cnt_m >= 50) {
				showError("Number of edges must be in range [0, 49]");
				return;
			}
			for (short j = 0; j < 3; ++j) {
				input_value[cnt_m][j] = v[j];
			}
		}
		file.close();

		n = 0;
		m = cnt_m;
		for (short i = 1; i <= cnt_m; ++i) {
			n = std::max(int(n), input_value[i][0]);
			n = std::max(int(n), input_value[i][1]);
			E[i].first = input_value[i][0];
			E[i].second = input_value[i][1];
			W[i] = input_value[i][2];
		}
		Refresh();
	}
	else {
		showError("Cannot open file");
	}
}

// create a random graph
void graph::randomGraph() {
	n = getRandom(3, 12);
	m = getRandom(2, std::min((n * (n - 1)) >> 1, 20));
	for (short i = 1; i <= 15; ++i) {
		V[i] = std::make_pair(getRandom(100, 700), getRandom(100, 500));
		T[i] = i;
		for (short j = 0; j < 3; ++j) {
			cv[j][i] = black[j];
		}
	}
	for (short i = 1; i <= m; ++i) {
		short x, y;
		do {
			x = getRandom(1, n);
			y = getRandom(1, n);
		} while (x == y);
		E[i] = std::make_pair(x, y);
		W[i] = 0;
		for (short j = 0; j < 3; ++j) {
			ce[j][i] = black[j];
		}
	}
}

void graph::onLeftDown(wxMouseEvent& e) {
	for (short i = 1; i <= n; ++i) {
		wxRect insideRect(V[i].first - rad[sz], V[i].second - rad[sz], rad[sz] << 2, rad[sz] << 2);
		if (insideRect.Contains(e.GetPosition())) {
			drag[i] = true;
			break;
		}
	}
}

void graph::onLeftUp(wxMouseEvent& e) {
	for (short i = 1; i <= n; ++i) {
		drag[i] = false;
	}
}

void graph::onMouseMove(wxMouseEvent& e) {
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

void graph::onPaint(wxPaintEvent& e) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	
	// draw edge
	for (short i = 1; i <= m; ++i) {
		dc.SetPen(wxPen(wxColour(ce[0][i], ce[1][i], ce[2][i]), 1));
		dc.DrawLine(wxPoint(V[E[i].first].first, V[E[i].first].second), wxPoint(V[E[i].second].first, V[E[i].second].second));
		if (W[i] != 0) {
			wxString text = "";
			text << W[i];
			dc.DrawText(text, wxPoint((V[E[i].first].first + V[E[i].second].first) / 2.0, (V[E[i].first].second + V[E[i].second].second) / 2.0));
		}
	}

	// draw vertex
	for (short i = 1; i <= n; ++i) {
		dc.SetPen(wxPen(wxColour(cv[0][i], cv[1][i], cv[2][i]), 1));

		if (style == 0) {
			dc.DrawCircle(wxPoint(V[i].first, V[i].second), rad[sz]);
		}
		else {
			dc.DrawRectangle(wxPoint(V[i].first - rad[sz], V[i].second - rad[sz]), wxSize(rad[sz] << 1, rad[sz] << 1));
		}

		wxString text = "";
		text << T[i];
		dc.DrawText(text, wxPoint(V[i].first - 4, V[i].second - 6));
	}
}

void graph::reDraw(wxCommandEvent& e) {
	style = button_style->GetSelection();
	sz = button_size->GetSelection();
	Refresh();
}