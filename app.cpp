#include "app.h"
#include "main.h"
#include "menu.h"

wxIMPLEMENT_APP(app);

bool app::OnInit() {
	//wxInitAllImageHandlers();
	main* main_frame = new main("Testing");
	main_frame->SetMinSize(wxSize(1100, 700));
	main_frame->SetMaxSize(wxSize(1100, 700));
	main_frame->SetClientSize(1090, 690);
	main_frame->Center();
	main_frame->Show();

	return true;
}