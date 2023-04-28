#include "app.h"
#include "Umain.h"

wxIMPLEMENT_APP(app);

bool app::OnInit() {
	wxInitAllImageHandlers();
	Umain* main_frame = new Umain("Terrible rip-off version of visualgo.net");
	main_frame->SetMinSize(wxSize(1100, 700));
	main_frame->SetMaxSize(wxSize(1100, 700));
	main_frame->SetClientSize(1090, 690);
	main_frame->Center();
	main_frame->Show();

	return true;
}