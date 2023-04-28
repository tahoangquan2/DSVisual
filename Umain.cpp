#include "receiver.h"
#include "Umain.h"
#include "Umenu.h"
#include "Usetting.h"
#include <wx/wx.h>

Umain::Umain(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	base->SetSize(1100, 700);

	Umenu* u_menu = new Umenu(base);
	u_menu->SetSize(1100, 700);

	Usetting* u_setting = new Usetting(base);
	u_setting->SetSize(1100, 700);
	u_setting->Hide();

	u_setting->parent = u_menu;
	u_menu->parent_setting = u_setting;

	u_menu->Show();
}