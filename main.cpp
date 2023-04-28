#include "main.h"
#include "menu.h"
#include "menu2.h"
#include <wx/wx.h>

main::main(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	bg->SetSize(700, 700);
	menu* ui1 = new menu(bg);
	ui1->SetSize(700, 700);
	menu2* ui2 = new menu2(bg);
	ui2->SetSize(700, 700);
	ui2->Hide();
	ui1->par = ui2;
	ui2->par = ui1;
	ui1->Show();
}