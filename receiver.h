#pragma once
#include "constant.h"
#include <wx/wx.h>

void drawBox(wxPanel** boxs, wxPanel* base, int pos, int value);

void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel);
void rClear(short id, wxPanel** boxs, wxPanel* base);
void rCreateRandom(short id, wxPanel** boxs, wxPanel* base);
