#include "Ustack.h"
#include "receiver.h"

// main page for UI stack
Ustack::Ustack(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(base, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	wxButton* button_create_random = new wxButton(base, wxID_ANY, "Create Random", wxPoint(70, 570), wxSize(110, 45));
	wxButton* button_import_file = new wxButton(base, wxID_ANY, "Import File", wxPoint(200, 570), wxSize(110, 45));
	wxButton* button_export_file = new wxButton(base, wxID_ANY, "Export File", wxPoint(200, 510), wxSize(110, 45));
	wxButton* button_insert = new wxButton(base, wxID_ANY, "Insert", wxPoint(330, 570), wxSize(110, 45));
	wxButton* button_delete = new wxButton(base, wxID_ANY, "Pop", wxPoint(460, 570), wxSize(110, 45));
	wxButton* button_clear = new wxButton(base, wxID_ANY, "Clear", wxPoint(590, 570), wxSize(110, 45));

	wxBitmap arrow_image(wxT("assets/arrow.png"), wxBITMAP_TYPE_PNG);
	arrow_image.Rescale(arrow_image, FromDIP(wxSize(30, 29)));
	arrow = new wxStaticBitmap(base, wxID_ANY, arrow_image, wxPoint(box_position[1] + 10, box_y - 50));
	arrow->Hide();

	arrow_image = wxBitmap(wxT("assets/arrow5.png"), wxBITMAP_TYPE_PNG);
	arrow_image.Rescale(arrow_image, FromDIP(wxSize(25, 30)));
	for (short i = 2; i <= max_size; ++i) {
		arrow2[i] = new wxStaticBitmap(base, wxID_ANY, arrow_image, wxPoint(box_position[i] - 25, box_y + 10));
		arrow2[i]->Hide();
	}

	wxStaticText* text_insert_val = new wxStaticText(base, wxID_ANY, "Value:", wxPoint(330, 512));

	input_insert_val = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(330, 530), wxSize(110, 25), wxSP_WRAP, -999, 999);

	button_back->Bind(wxEVT_BUTTON, &Ustack::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &Ustack::createRandom, this);
	button_import_file->Bind(wxEVT_BUTTON, &Ustack::importFile, this);
	button_export_file->Bind(wxEVT_BUTTON, &Ustack::exportFile, this);
	button_insert->Bind(wxEVT_BUTTON, &Ustack::insertValue, this);
	button_delete->Bind(wxEVT_BUTTON, &Ustack::popBack, this);
	button_clear->Bind(wxEVT_BUTTON, &Ustack::clearStack, this);

	wxCommandEvent empty_e = wxCommandEvent();
	createRandom(empty_e);
}

// go back to menu
void Ustack::goBack(wxCommandEvent& e) {
	wxCommandEvent empty_e = wxCommandEvent();
	createRandom(empty_e);
	rGoToPanel(this, parent);
}

// create random input
void Ustack::createRandom(wxCommandEvent& e) {
	rClear(id_stack, box, base);
	rCreateRandom(id_stack, box, base);

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_stack); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}

	input_insert_val->SetValue(0);
}

// import the outside file
void Ustack::importFile(wxCommandEvent& e) {
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
		rClear(id_stack, box, base);
		rStringToBox(id_stack, line, box, base);
	}
	else {
		showError(wxT("Cannot open file"));
	}

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_stack); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}

	input_insert_val->SetValue(0);
}

// export the input to a txt file
void Ustack::exportFile(wxCommandEvent& e) {
	if (rBoxSize(id_stack) == 0) {
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

	for (short i = 0; i <= max_size; ++i) {
		if (rAtBox(id_stack, i) == -1000) {
			break;
		}

		if (i > 0) {
			export_file << ",";
		}
		export_file << rAtBox(id_stack, i);
	}

	export_file.close();
}

// insert a value to a specific position
void Ustack::insertPosition(wxCommandEvent& e) {
	short pos = input_insert_pos;
	short val = input_insert_val->GetValue();

	rInsert(id_stack, pos, val, box, base);

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_stack); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}
}

// delete a value of a specific position
void Ustack::deletePosition(wxCommandEvent& e) {
	short pos = input_delete_pos;
	
	rDelete(id_stack, pos, box, base);

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_stack); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}

	input_insert_val->SetValue(0);
}

// push back a value
void Ustack::insertValue(wxCommandEvent& e) {
	input_insert_pos = rBoxSize(id_stack) + 1;
	wxCommandEvent empty_e = wxCommandEvent();
	insertPosition(empty_e);
}

// pop back a value
void Ustack::popBack(wxCommandEvent& e) {
	input_delete_pos = rBoxSize(id_stack);
	wxCommandEvent empty_e = wxCommandEvent();
	deletePosition(empty_e);
}

// pop back all elements in the stack
void Ustack::clearStack(wxCommandEvent& e) {
	rClear(id_stack, box, base);

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_stack); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}
}
