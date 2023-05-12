#include "Uqueue.h"
#include "receiver.h"

// main page for UI queue
Uqueue::Uqueue(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);

	wxButton* button_back = new wxButton(base, wxID_ANY, "Go back", wxPoint(10, 10), wxSize(100, 25));
	wxButton* button_create_random = new wxButton(base, wxID_ANY, "Create Random", wxPoint(70, 570), wxSize(110, 45));
	wxButton* button_import_file = new wxButton(base, wxID_ANY, "Import File", wxPoint(200, 570), wxSize(110, 45));
	wxButton* button_export_file = new wxButton(base, wxID_ANY, "Export File", wxPoint(200, 510), wxSize(110, 45));
	wxButton* button_insert = new wxButton(base, wxID_ANY, "Insert Back", wxPoint(330, 570), wxSize(110, 45));
	wxButton* button_insert2 = new wxButton(base, wxID_ANY, "Insert Front", wxPoint(330, 510), wxSize(110, 45));
	wxButton* button_delete = new wxButton(base, wxID_ANY, "Pop Back", wxPoint(460, 570), wxSize(110, 45));
	wxButton* button_delete2 = new wxButton(base, wxID_ANY, "Pop Front", wxPoint(460, 510), wxSize(110, 45));
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

	wxStaticText* text_insert_val = new wxStaticText(base, wxID_ANY, "Value:", wxPoint(330, 452));

	input_insert_val = new wxSpinCtrl(base, wxID_ANY, "", wxPoint(330, 470), wxSize(110, 25), wxSP_WRAP, -999, 999);

	button_back->Bind(wxEVT_BUTTON, &Uqueue::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &Uqueue::createRandom, this);
	button_import_file->Bind(wxEVT_BUTTON, &Uqueue::importFile, this);
	button_export_file->Bind(wxEVT_BUTTON, &Uqueue::exportFile, this);
	button_insert->Bind(wxEVT_BUTTON, &Uqueue::insertValue, this);
	button_insert2->Bind(wxEVT_BUTTON, &Uqueue::insertValue2, this);
	button_delete->Bind(wxEVT_BUTTON, &Uqueue::popBack, this);
	button_delete2->Bind(wxEVT_BUTTON, &Uqueue::popFront, this);
	button_clear->Bind(wxEVT_BUTTON, &Uqueue::clearQueue, this);

	wxCommandEvent empty_e = wxCommandEvent();
	createRandom(empty_e);
}

// go back to menu
void Uqueue::goBack(wxCommandEvent& e) {
	wxCommandEvent empty_e = wxCommandEvent();
	createRandom(empty_e);
	rGoToPanel(this, parent);
}

// create random input
void Uqueue::createRandom(wxCommandEvent& e) {
	rClear(id_queue, box, base);
	rCreateRandom(id_queue, box, base);

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_queue); ++i) {
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
void Uqueue::importFile(wxCommandEvent& e) {
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
		rClear(id_queue, box, base);
		rStringToBox(id_queue, line, box, base);
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

	for (short i = 1; i <= rBoxSize(id_queue); ++i) {
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
void Uqueue::exportFile(wxCommandEvent& e) {
	if (rBoxSize(id_queue) == 0) {
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
		if (rAtBox(id_queue, i) == -1000) {
			break;
		}

		if (i > 0) {
			export_file << ",";
		}
		export_file << rAtBox(id_queue, i);
	}

	export_file.close();
}

// insert a value to a specific position
void Uqueue::insertPosition(wxCommandEvent& e) {
	short pos = input_insert_pos;
	short val = input_insert_val->GetValue();

	rInsert(id_queue, pos, val, box, base);

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_queue); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}
}

// delete a value of a specific position
void Uqueue::deletePosition(wxCommandEvent& e) {
	short pos = input_delete_pos;

	rDelete(id_queue, pos, box, base);

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_queue); ++i) {
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
void Uqueue::insertValue(wxCommandEvent& e) {
	input_insert_pos = rBoxSize(id_queue) + 1;
	wxCommandEvent empty_e = wxCommandEvent();
	insertPosition(empty_e);
}

// push front a value
void Uqueue::insertValue2(wxCommandEvent& e) {
	input_insert_pos = 1;
	wxCommandEvent empty_e = wxCommandEvent();
	insertPosition(empty_e);
}

// pop back a value
void Uqueue::popBack(wxCommandEvent& e) {
	input_delete_pos = rBoxSize(id_queue);
	wxCommandEvent empty_e = wxCommandEvent();
	deletePosition(empty_e);
}

// pop front a value
void Uqueue::popFront(wxCommandEvent& e) {
	input_delete_pos = 1;
	wxCommandEvent empty_e = wxCommandEvent();
	deletePosition(empty_e);
}

// pop back all elements in the stack
void Uqueue::clearQueue(wxCommandEvent& e) {
	rClear(id_queue, box, base);

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_queue); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}
}
