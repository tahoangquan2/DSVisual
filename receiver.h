#pragma once
#include "constant.h"
#include <wx/wx.h>

void showError(wxString message);
void drawBox(wxPanel** boxs, wxPanel* base, short pos, int value);

void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel);
void rClear(short id, wxPanel** boxs, wxPanel* base);
void rCreateRandom(short id, wxPanel** boxs, wxPanel* base);
void rStringToBox(short id, std::string& line, wxPanel** boxs, wxPanel* base);
void rInsert(short id, short pos, int value, wxPanel** boxs, wxPanel* base);
void rDelete(short id, short pos, wxPanel** boxs, wxPanel* base);
void rUpdate(short id, short pos, int value, wxPanel** boxs, wxPanel* base);
short rSearch(short id, int value);

int rBoxSize(short id);
int rAtBox(short id, short pos);
