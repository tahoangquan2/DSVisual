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

	wxStaticText* text_insert_pos = new wxStaticText(base, wxID_ANY, "Position:", wxPoint(330, 512));
	wxStaticText* text_insert_val = new wxStaticText(base, wxID_ANY, "Value:", wxPoint(330, 452));
	wxStaticText* text_delete_pos = new wxStaticText(base, wxID_ANY, "Position:", wxPoint(460, 512));
	wxStaticText* text_update_pos = new wxStaticText(base, wxID_ANY, "Position:", wxPoint(590, 512));
	wxStaticText* text_update_val = new wxStaticText(base, wxID_ANY, "Value:", wxPoint(590, 452));
	wxStaticText* text_access_pos = new wxStaticText(base, wxID_ANY, "Position:", wxPoint(720, 512));
	wxStaticText* text_access_val = new wxStaticText(base, wxID_ANY, "Value:", wxPoint(720, 475));

	input_insert_pos = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(330, 530), wxSize(110, 25), wxSP_WRAP, 0, 0);
	input_insert_val = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(330, 470), wxSize(110, 25), wxSP_WRAP, -999, 999);
	input_delete_pos = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(460, 530), wxSize(110, 25), wxSP_WRAP, 0, 0);
	input_update_pos = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(590, 530), wxSize(110, 25), wxSP_WRAP, 0, 0);
	input_update_val = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(590, 470), wxSize(110, 25), wxSP_WRAP, -999, 999);
	input_access_pos = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(720, 530), wxSize(110, 25), wxSP_WRAP, 0, 0);

	button_back->Bind(wxEVT_BUTTON, &UstaticArray::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &UstaticArray::createRandom, this);
	button_import_file->Bind(wxEVT_BUTTON, &UstaticArray::importFile, this);
	button_export_file->Bind(wxEVT_BUTTON, &UstaticArray::exportFile, this);
	button_insert->Bind(wxEVT_BUTTON, &UstaticArray::insertPosition, this);
	button_delete->Bind(wxEVT_BUTTON, &UstaticArray::deletePosition, this);
	button_update->Bind(wxEVT_BUTTON, &UstaticArray::updatePosition, this);
	button_access->Bind(wxEVT_BUTTON, &UstaticArray::accessPosition, this);

	rClear(id_static_array, box, base);
	rCreateRandom(id_static_array, box, base);
	input_insert_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_delete_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_update_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_access_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_access_pos->SetRange(0, rBoxSize(id_static_array) - 1);
}

void UstaticArray::goBack(wxCommandEvent& e) {
	rGoToPanel(this, parent);
	rClear(id_static_array, box, base);
	rCreateRandom(id_static_array, box, base);
	output_access_val->Destroy();
}

void UstaticArray::createRandom(wxCommandEvent& e) {
	rClear(id_static_array, box, base);
	rCreateRandom(id_static_array, box, base);
	input_insert_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_delete_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_update_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_access_pos->SetRange(0, rBoxSize(id_static_array) - 1);
	input_access_pos->SetRange(0, rBoxSize(id_static_array) - 1);
}

void UstaticArray::importFile(wxCommandEvent& e) {
	wxFileDialog open_file_dialog(this, _("Open File"), "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (open_file_dialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	output_access_val->Destroy();
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
	short pos = input_insert_pos->GetValue();
	int value = input_insert_val->GetValue();
	output_access_val->Destroy();
	rInsert(id_static_array, pos, value, box, base);
}

void UstaticArray::deletePosition(wxCommandEvent& e) {
	short pos = input_delete_pos->GetValue();
	output_access_val->Destroy();
	rDelete(id_static_array, pos, box, base);
}

void UstaticArray::updatePosition(wxCommandEvent& e) {
	short pos = input_update_pos->GetValue();
	int value = input_update_val->GetValue();
	output_access_val->Destroy();
	rUpdate(id_static_array, pos, value, box, base);
}

void UstaticArray::accessPosition(wxCommandEvent& e) {
	short pos = input_access_pos->GetValue();
	int val = rAtBox(id_static_array, pos + 1);
	wxString text = "";
	text << val;
	
	output_access_val = new wxStaticText(base, wxID_ANY, text, wxPoint(775, 475));
}