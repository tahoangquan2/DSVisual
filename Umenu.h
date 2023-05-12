#include "constant.h"

// UI for the menu
class Umenu : public wxPanel {

public:
	wxPanel* base = new wxPanel(this);
	wxPanel* parent_setting = nullptr;
	wxPanel* parent_static_array = nullptr;
	wxPanel* parent_dynamic_array = nullptr;
	wxPanel* parent_simply_linked_list = nullptr;
	wxPanel* parent_doubly_linked_list = nullptr;
	wxPanel* parent_circular_linked_list = nullptr;

	Umenu(wxPanel* parent);
	void toSetting(wxCommandEvent& e);
	void toStaticArray(wxCommandEvent& e);
	void toDynamicArray(wxCommandEvent& e);
	void toSimplyLinkedList(wxCommandEvent& e);
	void toDoublyLinkedList(wxCommandEvent& e);
	void toCircularLinkedList(wxCommandEvent& e);

};
