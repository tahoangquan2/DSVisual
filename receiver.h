#include "constant.h"

// receive every signal from UI to the backend

// for receiver
void showError(wxString message);
void drawBox(wxPanel** boxs, wxPanel* base, short pos, short val);
void drawArrow(wxStaticBitmap* arrow, short pos);

// for UI
void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel);
void rClear(short id, wxPanel** boxs, wxPanel* base);
void rCreateRandom(short id, wxPanel** boxs, wxPanel* base);
void rStringToBox(short id, std::string& line, wxPanel** boxs, wxPanel* base);
void rInsert(short id, short pos, short val, wxPanel** boxs, wxPanel* base);
void rDelete(short id, short pos, wxPanel** boxs, wxPanel* base);
void rUpdate(short id, short pos, short val, wxPanel** boxs, wxPanel* base);
short rSearch(short id, short val);
bool rNext(short id, wxPanel** boxs, wxPanel* base, wxStaticBitmap* arrow);
void rInsertSbs(short id, short pos, short val, wxStaticBitmap* arrow);
void rDeleteSbs(short id, short pos, wxStaticBitmap* arrow);
void rUpdateSbs(short id, short pos, short val, wxStaticBitmap* arrow);
void rAccessSbs(short id, short pos, wxStaticBitmap* arrow);
void rSearchSbs(short id, short val, wxStaticBitmap* arrow);
int rBoxSize(short id);
int rAtBox(short id, short pos);
short rSbsMode(short id);
