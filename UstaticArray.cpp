#include "receiver.h"
#include "UstaticArray.h"
#include <wx/wx.h>
#include <fstream>

UstaticArray::UstaticArray(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(base, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	wxButton* button_create_random = new wxButton(base, wxID_ANY, "Create Random", wxPoint(70, 570), wxSize(110, 45));
	wxButton* button_import_file = new wxButton(base, wxID_ANY, "Import File", wxPoint(200, 570), wxSize(110, 45));
	wxButton* button_export_file = new wxButton(base, wxID_ANY, "Export File", wxPoint(200, 510), wxSize(110, 45));

	button_back->Bind(wxEVT_BUTTON, &UstaticArray::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &UstaticArray::createRandom, this);
	button_import_file->Bind(wxEVT_BUTTON, &UstaticArray::importFile, this);
	button_export_file->Bind(wxEVT_BUTTON, &UstaticArray::exportFile, this);
}

void UstaticArray::goBack(wxCommandEvent& e) {
	rGoToPanel(this, parent);
	rClear(id_static_array, box, base);
	rCreateRandom(id_static_array, box, base);
}

void UstaticArray::createRandom(wxCommandEvent& e) {
	rClear(id_static_array, box, base);
	rCreateRandom(id_static_array, box, base);
}

void UstaticArray::importFile(wxCommandEvent& e) {
	wxFileDialog open_file_dialog(this, _("Open File"), "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (open_file_dialog.ShowModal() == wxID_CANCEL) {
		return;
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