#pragma once
#include "constant.h"
#include <wx/wx.h>

void drawBox(wxPanel** boxs, wxPanel* base, short pos, int value);

void showError(wxString message);

void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel);
void rClear(short id, wxPanel** boxs, wxPanel* base);
void rCreateRandom(short id, wxPanel** boxs, wxPanel* base);
void rStringToBox(short id, std::string& line, wxPanel** boxs, wxPanel* base);