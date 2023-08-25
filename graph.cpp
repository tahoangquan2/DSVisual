#include "graph.h"
#include "receiver.h"

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
	wxButton* button_create_random = new wxButton(this, wxID_ANY, "Create Random", wxPoint(850, 60), wxSize(110, 45));
	wxButton* button_import_file = new wxButton(this, wxID_ANY, "Import File", wxPoint(850, 120), wxSize(110, 45));
	wxButton* button_cc = new wxButton(this, wxID_ANY, "Find CC", wxPoint(850, 180), wxSize(110, 45));
	wxButton* button_mst = new wxButton(this, wxID_ANY, "Find MST", wxPoint(850, 240), wxSize(110, 45));
	wxButton* button_sp = new wxButton(this, wxID_ANY, "Find SP", wxPoint(850, 300), wxSize(110, 45));

	button_style = new wxChoice(this, wxID_ANY, wxPoint(850, 600), wxSize(90, 60), choices_style);
	button_size = new wxChoice(this, wxID_ANY, wxPoint(950, 600), wxSize(90, 60), choices_size);

	wxStaticText* text_start = new wxStaticText(this, wxID_ANY, "Position:", wxPoint(850, 350));
	wxStaticText* text_end = new wxStaticText(this, wxID_ANY, "Value:", wxPoint(850, 400));

	input_start = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(850, 370), wxSize(110, 25), wxSP_WRAP, 1, 1);
	input_end = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(850, 420), wxSize(110, 25), wxSP_WRAP, 1, 1);

	button_style->Select(0);
	button_size->Select(0);

	SetCursor(wxCursor(wxCURSOR_HAND));

	Bind(wxEVT_LEFT_DOWN, &graph::onLeftDown, this);
	Bind(wxEVT_LEFT_UP, &graph::onLeftUp, this);
	Bind(wxEVT_MOTION, &graph::onMouseMove, this);
	Bind(wxEVT_PAINT, &graph::onPaint, this);

	button_back->Bind(wxEVT_BUTTON, &graph::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &graph::randomGraph, this);
	button_import_file->Bind(wxEVT_BUTTON, &graph::importFile, this);
	button_cc->Bind(wxEVT_BUTTON, &graph::findCC, this);
	button_mst->Bind(wxEVT_BUTTON, &graph::findMST, this);
	button_sp->Bind(wxEVT_BUTTON, &graph::findSP, this);
	button_style->Bind(wxEVT_CHOICE, &graph::reDraw, this);
	button_size->Bind(wxEVT_CHOICE, &graph::reDraw, this);

	wxCommandEvent empty_e = wxCommandEvent();
	randomGraph(empty_e);
}

// go back to menu
void graph::goBack(wxCommandEvent& e) {
	wxCommandEvent empty_e = wxCommandEvent();
	randomGraph(empty_e);
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
			E[i].second.first = input_value[i][0];
			E[i].second.second = input_value[i][1];
			E[i].first = input_value[i][2];
			ce[i][0] = ce[i][1] = ce[i][2] = 0;
		}

		for (short i = 1; i <= n; ++i) {
			cv[i][0] = cv[i][1] = cv[i][2] = 0;
		}

		Refresh();
	}
	else {
		showError("Cannot open file");
	}

	input_start->SetRange(1, n);
	input_end->SetRange(1, n);

	input_start->SetValue(1);
	input_end->SetValue(n);
}

// create a random graph
void graph::randomGraph(wxCommandEvent& e) {
	n = getRandom(3, 12);
	m = getRandom(2, std::min(((n * (n - 1)) >> 1) - 1, 20));
	for (short i = 1; i <= 15; ++i) {
		V[i] = std::make_pair(getRandom(100, 700), getRandom(100, 500));
		for (short j = 0; j < 3; ++j) {
			cv[i][j] = black[j];
		}
	}
	bool exist[16][16] = {};
	for (short i = 1; i <= m; ++i) {
		short x, y;
		do {
			x = getRandom(1, n);
			y = getRandom(1, n);
		} while (x == y || exist[x][y]);
		exist[x][y] = exist[y][x] = true;
		E[i] = std::make_pair(0, std::make_pair(x, y));
		for (short j = 0; j < 3; ++j) {
			ce[i][j] = black[j];
		}
	}

	input_start->SetRange(1, n);
	input_end->SetRange(1, n);

	input_start->SetValue(1);
	input_end->SetValue(n);

	Refresh();
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

// draw graph
void graph::onPaint(wxPaintEvent& e) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	
	// draw edge
	for (short i = 1; i <= m; ++i) {
		dc.SetPen(wxPen(wxColour(ce[i][0], ce[i][1], ce[i][2]), 1));
		dc.DrawLine(wxPoint(V[E[i].second.first].first, V[E[i].second.first].second), wxPoint(V[E[i].second.second].first, V[E[i].second.second].second));
		if (E[i].first != 0) {
			wxString text = "";
			text << E[i].first;
			dc.DrawText(text, wxPoint((V[E[i].second.first].first + V[E[i].second.second].first) / 2.0, (V[E[i].second.first].second + V[E[i].second.second].second) / 2.0));
		}
	}

	// draw vertex
	wxString text, tt = "";
	for (short i = 1; i <= n; ++i) {
		dc.SetPen(wxPen(wxColour(cv[i][0], cv[i][1], cv[i][2]), 2));

		if (style == 0) {
			dc.DrawCircle(wxPoint(V[i].first, V[i].second), rad[sz]);
		}
		else {
			dc.DrawRectangle(wxPoint(V[i].first - rad[sz], V[i].second - rad[sz]), wxSize(rad[sz] << 1, rad[sz] << 1));
		}

		text = "";
		text << i;
		dc.DrawText(text, wxPoint(V[i].first - 4, V[i].second - 6));
	}
}

void graph::reDraw(wxCommandEvent& e) {
	style = button_style->GetSelection();
	sz = button_size->GetSelection();
	Refresh();
}

// find connected components
void graph::dfsCC(short u) {
	vis[u] = true;
	cv[u][0] = x;
	cv[u][1] = y;
	cv[u][2] = z;
	for (int i = 1; i <= m; ++i) {
		if (E[i].second.first == u || E[i].second.second == u) {
			if (vis[E[i].second.first] == false) {
				dfsCC(E[i].second.first);
			}
			if (vis[E[i].second.second] == false) {
				dfsCC(E[i].second.second);
			}
		}
	}
}

void graph::findCC(wxCommandEvent& e) {
	for (short i = 1; i <= m; ++i) {
		ce[i][0] = ce[i][1] = ce[i][2] = 0;
	}

	for (short i = 1; i <= n; ++i) {
		cv[i][0] = cv[i][1] = cv[i][2] = 0;
	}

	memset(vis, false, sizeof(vis));
	for (short i = 1; i <= n; ++i) {
		if (vis[i]) {
			continue;
		}
		x = getRandom(0, 255);
		y = getRandom(0, 255);
		z = getRandom(0, 255);
		dfsCC(i);
	}
	Refresh();
}

// find minimum spanning tree
short graph::par(short u) {
	if (cha[u] > 0) {
		return par(cha[u]);
	}
	return u;
}

void graph::findMST(wxCommandEvent& e) {
	for (short i = 1; i <= m; ++i) {
		ce[i][0] = ce[i][1] = ce[i][2] = 0;
	}

	for (short i = 1; i <= n; ++i) {
		cv[i][0] = cv[i][1] = cv[i][2] = 0;
	}

	memset(cha, -1, sizeof(cha));
	sort(E + 1, E + 1 + m);
	x = getRandom(0, 255);
	y = getRandom(0, 255);
	z = getRandom(0, 255);
	for (short i = 1; i <= m; ++i) {
		short u = E[i].second.first;
		short v = E[i].second.second;
		if (par(u) != par(v)) {
			cv[u][0] = cv[v][0] = x;
			cv[u][1] = cv[v][1] = y;
			cv[u][2] = cv[v][2] = z;
			u = par(u);
			v = par(v);
			cha[u] += cha[v];
			cha[v] = u;
			ce[i][0] = x;
			ce[i][1] = y;
			ce[i][2] = z;
		}
	}

	Refresh();
}

// find shortest path
void graph::findSP(wxCommandEvent& e) {
	for (short i = 1; i <= m; ++i) {
		ce[i][0] = ce[i][1] = ce[i][2] = 0;
	}

	for (short i = 1; i <= n; ++i) {
		cv[i][0] = cv[i][1] = cv[i][2] = 0;
	}

	short st = input_start->GetValue();
	short en = input_end->GetValue();

	memset(dis, 63, sizeof(dis));
	memset(vis, false, sizeof(vis));
	dis[st] = 0;
	vis[st] = true;
	short mi;

	for (short j = 1; j <= n; ++j) {
		mi = 0;
		for (short i = 1; i <= m; ++i) {
			short u = E[i].second.first;
			short v = E[i].second.second;
			if (vis[v] == true && vis[u] == false && dis[v] + E[i].first < dis[u]) {
				dis[u] = dis[v] + E[i].first;
				tr[u] = v;
			}
			if (vis[u] == true && vis[v] == false && dis[u] + E[i].first < dis[v]) {
				dis[v] = dis[u] + E[i].first;
				tr[v] = u;
			}
		}
		for (short i = 1; i <= n; ++i) {
			if (vis[i] == true) {
				continue;
			}
			if (dis[mi] > dis[i]) {
				mi = i;
			}
		}
		if (mi == 0) {
			break;
		}
		vis[mi] = true;
	}

	if (dis[en] < dis[0]) {
		x = getRandom(0, 255);
		y = getRandom(0, 255);
		z = getRandom(0, 255);
		while (en != st) {
			for (short i = 1; i <= m; ++i) {
				short u = E[i].second.first;
				short v = E[i].second.second;
				if ((u == en && v == tr[en]) || ((v == en && u == tr[en]))) {
					cv[u][0] = cv[v][0] = x;
					cv[u][1] = cv[v][1] = y;
					cv[u][2] = cv[v][2] = z;
					ce[i][0] = x;
					ce[i][1] = y;
					ce[i][2] = z;
				}
			}
			en = tr[en];
		}
	}

	Refresh();
}
