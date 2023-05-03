#include "app.h"

wxIMPLEMENT_APP(app);

bool app::OnInit() {
	wxInitAllImageHandlers();
	Umain* main_frame = new Umain("Terrible rip-off version of visualgo.net");
	main_frame->SetMinSize(wxSize(size1, size2));
	main_frame->SetMaxSize(wxSize(size1, size2));
	main_frame->SetClientSize(wxSize(size1, size2));
	main_frame->Center();
	main_frame->Show();

	return true;
}
