#include "Umain.h"
#include "Umenu.h"
#include "Usetting.h"
#include "UstaticArray.h"

// UI for the main frame
Umain::Umain(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxIcon icon("assets/icon.jpg", wxBITMAP_TYPE_JPEG);
	SetIcon(icon);
	base->SetSize(size1, size2);

	Umenu* u_menu = new Umenu(base);
	u_menu->SetSize(size1, size2);

	Usetting* u_setting = new Usetting(base);
	u_setting->SetSize(size1, size2);
	u_setting->Hide();

	UstaticArray* u_static_array = new UstaticArray(base);
	u_static_array->SetSize(size1, size2);
	u_static_array->Hide();

	u_setting->parent = u_menu;
	u_static_array->parent = u_menu;
	u_menu->parent_setting = u_setting;
	u_menu->parent_static_array = u_static_array;

	u_menu->Show();
}