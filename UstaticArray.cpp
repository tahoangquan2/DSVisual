#include "constant.h"
#include "receiver.h"
#include "UstaticArray.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <fstream>

UstaticArray::UstaticArray(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(base, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	wxButton* button_create_random = new wxButton(base, wxID_ANY, "Create Random", wxPoint(70, 570), wxSize(110, 45));
	wxButton* button_import_file = new wxButton(base, wxID_ANY, "Import File", wxPoint(200, 570), wxSize(110, 45));
	wxButton* button_export_file = new wxButton(base, wxID_ANY, "Export File", wxPoint(200, 510), wxSize(110, 45));
	wxButton* button_insert = new wxButton(base, wxID_ANY, "Insert", wxPoint(330, 570), wxSize(110, 45));
	wxButton* button_delete = new wxButton(base, wxID_ANY, "Delete", wxPoint(460, 570), wxSize(110, 45));
	wxButton* button_update = new wxButton(base, wxID_ANY, "Update", wxPoint(590, 570), wxSize(110, 45));
	wxButton* button_access = new wxButton(base, wxID_ANY, "Access", wxPoint(720, 570), wxSize(110, 45));
	wxButton* button_search = new wxButton(base, wxID_ANY, "Search", wxPoint(850, 570), wxSize(110, 45));
	button_sbs = new wxButton(base, wxID_ANY, "Step by Step", wxPoint(330, 10), wxSize(110, 45));
	button_sbs2 = new wxButton(base, wxID_ANY, "Back to Normal", wxPoint(330, 10), wxSize(110, 45));
	button_sbs2->Hide();
	button_next = new wxButton(base, wxID_ANY, "Next", wxPoint(460, 10), wxSize(110, 45));
	button_next->Hide();
	button_skip = new wxButton(base, wxID_ANY, "Skip", wxPoint(590, 10), wxSize(110, 45));
	button_skip->Hide();

	wxBitmap arrow_image(wxT("assets/arrow.png"), wxBITMAP_TYPE_PNG);
	arrow_image.Rescale(arrow_image, FromDIP(wxSize(30, 29)));
	arrow = new wxStaticBitmap(base, wxID_ANY, arrow_image, wxPoint(box_position[1] + 10, box_y - 50));
	arrow->Hide();

	wxStaticText* text_insert_pos = new wxStaticText(base, wxID_ANY, "Position:", wxPoint(330, 512));
	wxStaticText* text_insert_val = new wxStaticText(base, wxID_ANY, "Value:", wxPoint(330, 452));
	wxStaticText* text_delete_pos = new wxStaticText(base, wxID_ANY, "Position:", wxPoint(460, 512));
	wxStaticText* text_update_pos = new wxStaticText(base, wxID_ANY, "Position:", wxPoint(590, 512));
	wxStaticText* text_update_val = new wxStaticText(base, wxID_ANY, "Value:", wxPoint(590, 452));
	wxStaticText* text_access_pos = new wxStaticText(base, wxID_ANY, "Position:", wxPoint(720, 512));
	wxStaticText* text_access_val = new wxStaticText(base, wxID_ANY, "Value:", wxPoint(720, 475));
	wxStaticText* text_search_pos = new wxStaticText(base, wxID_ANY, "Value:", wxPoint(850, 512));
	wxStaticText* text_search_val = new wxStaticText(base, wxID_ANY, "Position:", wxPoint(850, 475));

	input_insert_pos = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(330, 530), wxSize(110, 25), wxSP_WRAP, 0, 0);
	input_insert_val = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(330, 470), wxSize(110, 25), wxSP_WRAP, -999, 999);
	input_delete_pos = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(460, 530), wxSize(110, 25), wxSP_WRAP, 0, 0);
	input_update_pos = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(590, 530), wxSize(110, 25), wxSP_WRAP, 0, 0);
	input_update_val = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(590, 470), wxSize(110, 25), wxSP_WRAP, -999, 999);
	input_access_pos = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(720, 530), wxSize(110, 25), wxSP_WRAP, 0, 0);
	input_search_val = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(850, 530), wxSize(110, 25), wxSP_WRAP, -999, 999);

	button_back->Bind(wxEVT_BUTTON, &UstaticArray::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &UstaticArray::createRandom, this);
	button_import_file->Bind(wxEVT_BUTTON, &UstaticArray::importFile, this);
	button_export_file->Bind(wxEVT_BUTTON, &UstaticArray::exportFile, this);
	button_insert->Bind(wxEVT_BUTTON, &UstaticArray::insertPosition, this);
	button_delete->Bind(wxEVT_BUTTON, &UstaticArray::deletePosition, this);
	button_update->Bind(wxEVT_BUTTON, &UstaticArray::updatePosition, this);
	button_access->Bind(wxEVT_BUTTON, &UstaticArray::accessPosition, this);
	button_search->Bind(wxEVT_BUTTON, &UstaticArray::searchValue, this);
	button_sbs->Bind(wxEVT_BUTTON, &UstaticArray::sbsModeOn, this);
	button_sbs2->Bind(wxEVT_BUTTON, &UstaticArray::sbsModeOff, this);
	button_next->Bind(wxEVT_BUTTON, &UstaticArray::nextStep, this);
	button_skip->Bind(wxEVT_BUTTON, &UstaticArray::skipStep, this);

	wxCommandEvent empty_e = wxCommandEvent();
	createRandom(empty_e);
}

void UstaticArray::goBack(wxCommandEvent& e) {
	rGoToPanel(this, parent);
	wxCommandEvent empty_e = wxCommandEvent();
	sbsModeOff(empty_e);
	createRandom(empty_e);
}

void UstaticArray::createRandom(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}
	rClear(id_static_array, box, base);
	rCreateRandom(id_static_array, box, base);
	input_insert_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_delete_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_update_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_access_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	if (output_access_val != nullptr) {
		output_access_val->Destroy();
		output_access_val = nullptr;
	}
	if (output_search_pos != nullptr) {
		output_search_pos->Destroy();
		output_search_pos = nullptr;
	}
	input_insert_pos->SetValue(0);
	input_insert_val->SetValue(0);
	input_delete_pos->SetValue(0);
	input_update_pos->SetValue(0);
	input_update_val->SetValue(0);
	input_access_pos->SetValue(0);
	input_search_val->SetValue(0);
}

void UstaticArray::importFile(wxCommandEvent& e) {
	wxFileDialog open_file_dialog(this, _("Open File"), "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (open_file_dialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	if (output_access_val != nullptr) {
		output_access_val->Destroy();
		output_access_val = nullptr;
	}
	if (output_search_pos != nullptr) {
		output_search_pos->Destroy();
		output_search_pos = nullptr;
	}

	wxString file_path = open_file_dialog.GetPath();
	std::ifstream file(file_path.ToStdString());

	if (file.is_open()) {
		std::string line;
		std::getline(file, line);
		file.close();
		line = "," + line;
		rClear(id_static_array, box, base);
		rStringToBox(id_static_array, line, box, base);
		input_insert_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	}
	else {
		showError(wxT("Cannot open file"));
	}
}

void UstaticArray::exportFile(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}
	if (rBoxSize(id_static_array) == 0) {
		showError("There is no element");
		return;
	}

	wxFileDialog save_file_dialog(this, _("Export File"), "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (save_file_dialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	wxString selected_file_path = save_file_dialog.GetPath();
	std::ofstream export_file;
	std::string file_path = std::string(selected_file_path.mb_str());

	export_file.open(file_path, std::ofstream::out);

	for (short i = 1; i <= max_size; ++i) {
		if (rAtBox(id_static_array, i) == -1000) {
			break;
		}

		if (i > 1) {
			export_file << ",";
		}
		export_file << rAtBox(id_static_array, i);
	}

	export_file.close();
}

void UstaticArray::insertPosition(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}
	short pos = input_insert_pos->GetValue();
	int value = input_insert_val->GetValue();
	if (output_access_val != nullptr) {
		output_access_val->Destroy();
		output_access_val = nullptr;
	}
	if (output_search_pos != nullptr) {
		output_search_pos->Destroy();
		output_search_pos = nullptr;
	}
	if (sbs_mode == false) {
		rInsert(id_static_array, pos, value, box, base);
	}
	else {
		fix_pos = pos;
		fix_val = value;
		during_sbs = true;
		rInsertSbs(id_static_array, pos, value, arrow);
	}
}

void UstaticArray::deletePosition(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}
	short pos = input_delete_pos->GetValue();
	if (output_access_val != nullptr) {
		output_access_val->Destroy();
		output_access_val = nullptr;
	}
	if (output_search_pos != nullptr) {
		output_search_pos->Destroy();
		output_search_pos = nullptr;
	}
	rDelete(id_static_array, pos, box, base);
}

void UstaticArray::updatePosition(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}
	short pos = input_update_pos->GetValue();
	int value = input_update_val->GetValue();
	if (output_access_val != nullptr) {
		output_access_val->Destroy();
		output_access_val = nullptr;
	}
	if (output_search_pos != nullptr) {
		output_search_pos->Destroy();
		output_search_pos = nullptr;
	}
	rUpdate(id_static_array, pos, value, box, base);
}

void UstaticArray::accessPosition(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}
	short pos = input_access_pos->GetValue();
	int value = rAtBox(id_static_array, pos + 1);
	wxString text = "";
	text << value;

	if (output_access_val != nullptr) {
		output_access_val->Destroy();
		output_access_val = nullptr;
	}
	output_access_val = new wxStaticText(base, wxID_ANY, text, wxPoint(775, 475));
	output_access_val->Show();
}

void UstaticArray::searchValue(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}
	int value = input_search_val->GetValue();
	short pos = rSearch(id_static_array, value);
	wxString text = "";

	if (pos == -1) {
		text = "None";
	}
	else {
		text << pos;
	}

	if (output_search_pos != nullptr) {
		output_search_pos->Destroy();
		output_search_pos = nullptr;
	}
	output_search_pos = new wxStaticText(base, wxID_ANY, text, wxPoint(905, 475));
	output_search_pos->Show();
}

void UstaticArray::sbsModeOn(wxCommandEvent& e) {
	sbs_mode = true;
	button_sbs->Hide();
	button_sbs2->Show();
	button_next->Show();
	button_skip->Show();
	arrow->SetPosition(wxPoint(box_position[1] + 10, box_y - 50));
	arrow->Show();
}

void UstaticArray::sbsModeOff(wxCommandEvent& e) {
	sbs_mode = false;
	button_sbs2->Hide();
	button_sbs->Show();
	button_next->Hide();
	button_skip->Hide();
	arrow->Hide();
	wxCommandEvent empty_e = wxCommandEvent();
	skipStep(empty_e);
}

void UstaticArray::nextStep(wxCommandEvent& e) {
	if (during_sbs == false) {
		return;
	}
	if (rNext(id_static_array, box, base, arrow)) {
		during_sbs = false;
		wxCommandEvent empty_e = wxCommandEvent();
		switch (rSbsMode(id_static_array)) {
		case 1:
			rInsert(id_static_array, fix_pos, fix_val, box, base);
			break;
		}
	}
}

void UstaticArray::skipStep(wxCommandEvent& e) {
	if (during_sbs == false) {
		return;
	}
	during_sbs = false;
	wxCommandEvent empty_e = wxCommandEvent();
	switch (rSbsMode(id_static_array)) {
	case 1:
		rInsert(id_static_array, fix_pos, fix_val, box, base);
		break;
	}
}