#include "UsimplyLinkedList.h"
#include "receiver.h"

// main page for UI simply linked list
UsimplyLinkedList::UsimplyLinkedList(wxPanel* parent) : wxPanel(parent) {
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

	// for step by step mode
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

	arrow_image = wxBitmap(wxT("assets/arrow2.png"), wxBITMAP_TYPE_PNG);
	arrow_image.Rescale(arrow_image, FromDIP(wxSize(25, 30)));
	for (short i = 2; i <= max_size; ++i) {
		arrow2[i] = new wxStaticBitmap(base, wxID_ANY, arrow_image, wxPoint(box_position[i] - 25, box_y + 10));
		arrow2[i]->Hide();
	}

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

	button_back->Bind(wxEVT_BUTTON, &UsimplyLinkedList::goBack, this);
	button_create_random->Bind(wxEVT_BUTTON, &UsimplyLinkedList::createRandom, this);
	button_import_file->Bind(wxEVT_BUTTON, &UsimplyLinkedList::importFile, this);
	button_export_file->Bind(wxEVT_BUTTON, &UsimplyLinkedList::exportFile, this);
	button_insert->Bind(wxEVT_BUTTON, &UsimplyLinkedList::insertPosition, this);
	button_delete->Bind(wxEVT_BUTTON, &UsimplyLinkedList::deletePosition, this);
	button_update->Bind(wxEVT_BUTTON, &UsimplyLinkedList::updatePosition, this);
	button_access->Bind(wxEVT_BUTTON, &UsimplyLinkedList::accessPosition, this);
	button_search->Bind(wxEVT_BUTTON, &UsimplyLinkedList::searchValue, this);

	button_sbs->Bind(wxEVT_BUTTON, &UsimplyLinkedList::sbsModeOn, this);
	button_sbs2->Bind(wxEVT_BUTTON, &UsimplyLinkedList::sbsModeOff, this);
	button_next->Bind(wxEVT_BUTTON, &UsimplyLinkedList::nextStep, this);
	button_skip->Bind(wxEVT_BUTTON, &UsimplyLinkedList::skipStep, this);

	wxCommandEvent empty_e = wxCommandEvent();
	createRandom(empty_e);
}

// go back to menu
void UsimplyLinkedList::goBack(wxCommandEvent& e) {
	wxCommandEvent empty_e = wxCommandEvent();
	sbsModeOff(empty_e);
	createRandom(empty_e);
	rGoToPanel(this, parent);
}

// create random input
void UsimplyLinkedList::createRandom(wxCommandEvent& e) {
	if (during_sbs == true) {
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

	rClear(id_simply_linked_list, box, base);
	rCreateRandom(id_simply_linked_list, box, base);

	for (short i = 1; i <= max_size; ++i) {
		if (id_pos[i] != nullptr) {
			id_pos[i]->Destroy();
			id_pos[i] = nullptr;
		}

		if (i > 1) {
			arrow2[i]->Hide();
		}
	}

	for (short i = 1; i <= rBoxSize(id_simply_linked_list); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}

	input_insert_pos->SetRange(0, rBoxSize(id_simply_linked_list));
	input_delete_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);
	input_update_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);
	input_access_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);

	input_insert_pos->SetValue(0);
	input_insert_val->SetValue(0);
	input_delete_pos->SetValue(0);
	input_update_pos->SetValue(0);
	input_update_val->SetValue(0);
	input_access_pos->SetValue(0);
	input_search_val->SetValue(0);
}

// import the outside file
void UsimplyLinkedList::importFile(wxCommandEvent& e) {
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
		rClear(id_simply_linked_list, box, base);
		rStringToBox(id_simply_linked_list, line, box, base);
		input_insert_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);
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

	for (short i = 1; i <= rBoxSize(id_simply_linked_list); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}

	input_insert_pos->SetRange(0, rBoxSize(id_simply_linked_list));
	input_delete_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);
	input_update_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);
	input_access_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);

	input_insert_pos->SetValue(0);
	input_insert_val->SetValue(0);
	input_delete_pos->SetValue(0);
	input_update_pos->SetValue(0);
	input_update_val->SetValue(0);
	input_access_pos->SetValue(0);
	input_search_val->SetValue(0);
}

// export the input to a txt file
void UsimplyLinkedList::exportFile(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}

	if (rBoxSize(id_simply_linked_list) == 0) {
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
		if (rAtBox(id_simply_linked_list, i) == -1000) {
			break;
		}

		if (i > 0) {
			export_file << ",";
		}
		export_file << rAtBox(id_simply_linked_list, i);
	}

	export_file.close();
}

// insert a value to a specific position
void UsimplyLinkedList::insertPosition(wxCommandEvent& e) {
	if (during_sbs == true) {
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

	short pos = input_insert_pos->GetValue();
	short val = input_insert_val->GetValue();

	if (sbs_mode == false || skip_sbs == true) {
		rInsert(id_simply_linked_list, pos, val, box, base);
		skip_sbs = false;
	}
	else {
		during_sbs = true;
		fix_pos = pos;
		fix_val = val;
		if (rBoxSize(id_simply_linked_list) == max_size) {
			during_sbs = false;
			showError("The maximum number of element you can have is 12");
			return;
		}
		else {
			rInsertSbs(id_simply_linked_list, pos, val, arrow);
		}
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

	for (short i = 1; i <= rBoxSize(id_simply_linked_list); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}

	input_insert_pos->SetRange(0, rBoxSize(id_simply_linked_list));
	input_delete_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);
	input_update_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);
	input_access_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);

	input_delete_pos->SetValue(0);
	input_update_pos->SetValue(0);
	input_update_val->SetValue(0);
	input_access_pos->SetValue(0);
	input_search_val->SetValue(0);
}

// delete a value of a specific position
void UsimplyLinkedList::deletePosition(wxCommandEvent& e) {
	if (during_sbs == true) {
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

	short pos = input_delete_pos->GetValue();

	if (sbs_mode == false || skip_sbs == true) {
		rDelete(id_simply_linked_list, pos, box, base);
		skip_sbs = false;
	}
	else {
		during_sbs = true;
		fix_pos = pos;
		rDeleteSbs(id_simply_linked_list, pos, arrow);
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

	for (short i = 1; i <= rBoxSize(id_simply_linked_list); ++i) {
		wxString display_value = "";
		display_value << (i - 1);
		id_pos[i] = new wxStaticText(base, wxID_ANY, display_value, wxPoint(box_position[i] + 20, box_y + 60));

		if (i > 1) {
			arrow2[i]->Show();
		}
	}

	input_insert_pos->SetRange(0, rBoxSize(id_simply_linked_list));
	input_delete_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);
	input_update_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);
	input_access_pos->SetRange(0, rBoxSize(id_simply_linked_list) - 1);

	input_insert_pos->SetValue(0);
	input_insert_val->SetValue(0);
	input_update_val->SetValue(0);
	input_access_pos->SetValue(0);
	input_search_val->SetValue(0);
}

// update a value of a specific position
void UsimplyLinkedList::updatePosition(wxCommandEvent& e) {
	if (during_sbs == true) {
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

	short pos = input_update_pos->GetValue();
	short val = input_update_val->GetValue();

	if (sbs_mode == false || skip_sbs == true) {
		rUpdate(id_simply_linked_list, pos, val, box, base);
		skip_sbs = false;
	}
	else {
		during_sbs = true;
		fix_pos = pos;
		fix_val = val;
		rUpdateSbs(id_simply_linked_list, pos, val, arrow);
	}
}

// return the value at a specific position
void UsimplyLinkedList::accessPosition(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}

	if (output_access_val != nullptr) {
		output_access_val->Destroy();
		output_access_val = nullptr;
	}

	short pos = input_access_pos->GetValue();

	if (sbs_mode == false || skip_sbs == true) {
		skip_sbs = false;
		wxString text = "";
		text << rAtBox(id_simply_linked_list, pos);
		output_access_val = new wxStaticText(base, wxID_ANY, text, wxPoint(775, 475));
		output_access_val->Show();
	}
	else {
		during_sbs = true;
		fix_pos = pos;
		rAccessSbs(id_simply_linked_list, pos, arrow);
	}
}

// search the position of first appearence of a specific value
void UsimplyLinkedList::searchValue(wxCommandEvent& e) {
	if (during_sbs == true) {
		return;
	}

	if (output_search_pos != nullptr) {
		output_search_pos->Destroy();
		output_search_pos = nullptr;
	}

	short val = input_search_val->GetValue();

	if (sbs_mode == false || skip_sbs == true) {
		skip_sbs = false;
		short pos = rSearch(id_simply_linked_list, val);
		wxString text = "";

		if (pos == -1) {
			text = "None";
		}
		else {
			text << pos;
		}

		output_search_pos = new wxStaticText(base, wxID_ANY, text, wxPoint(905, 475));
		output_search_pos->Show();
	}
	else {
		during_sbs = true;
		fix_val = val;
		rSearchSbs(id_simply_linked_list, val, arrow);
	}
}

// turn on the step by step mode
void UsimplyLinkedList::sbsModeOn(wxCommandEvent& e) {
	sbs_mode = true;
	skip_sbs = false;
	button_sbs->Hide();
	button_sbs2->Show();
	button_next->Show();
	button_skip->Show();
	arrow->SetPosition(wxPoint(box_position[1] + 10, box_y - 50));
	arrow->Show();
}

// turn off the step by step mode
void UsimplyLinkedList::sbsModeOff(wxCommandEvent& e) {
	wxCommandEvent empty_e = wxCommandEvent();
	skipStep(empty_e);

	sbs_mode = false;
	skip_sbs = false;
	button_sbs2->Hide();
	button_sbs->Show();
	button_next->Hide();
	button_skip->Hide();
	arrow->Hide();
}

// go to the next step in the step by step mode
void UsimplyLinkedList::nextStep(wxCommandEvent& e) {
	if (during_sbs == false) {
		return;
	}

	if (rNext(id_simply_linked_list, box, base, arrow) == true) {
		wxCommandEvent empty_e = wxCommandEvent();
		skipStep(empty_e);
		during_sbs = false;
	}
}

// skipp all the steps in the step by step mode
void UsimplyLinkedList::skipStep(wxCommandEvent& e) {
	if (during_sbs == false) {
		return;
	}

	wxCommandEvent empty_e = wxCommandEvent();
	wxString text = "";
	short pos;
	during_sbs = false;
	skip_sbs = true;

	switch (rSbsMode(id_simply_linked_list)) {
	case 1:
		input_insert_pos->SetValue(fix_pos);
		input_insert_val->SetValue(fix_val);
		insertPosition(empty_e);
		break;

	case 2:
		input_delete_pos->SetValue(fix_pos);
		deletePosition(empty_e);
		break;

	case 3:
		input_update_pos->SetValue(fix_pos);
		input_insert_val->SetValue(fix_val);
		updatePosition(empty_e);
		break;

	case 4:
		text << rAtBox(id_simply_linked_list, fix_pos);
		output_access_val = new wxStaticText(base, wxID_ANY, text, wxPoint(775, 475));
		output_access_val->Show();
		skip_sbs = false;
		break;

	case 5:
		pos = rSearch(id_simply_linked_list, fix_val);
		skip_sbs = false;

		if (pos == -1) {
			text = "None";
		}
		else {
			text << pos;
		}

		output_search_pos = new wxStaticText(base, wxID_ANY, text, wxPoint(905, 475));
		output_search_pos->Show();
		break;
	}
}
