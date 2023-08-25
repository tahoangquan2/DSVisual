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
	wxPanel* parent_stack = nullptr;
	wxPanel* parent_queue = nullptr;
	wxPanel* parent_graph = nullptr;
	wxPanel* parent_hash_table = nullptr;
	wxPanel* parent_max_heap = nullptr;

	Umenu(wxPanel* parent);
	void toSetting(wxCommandEvent& e);
	void toStaticArray(wxCommandEvent& e);
	void toDynamicArray(wxCommandEvent& e);
	void toSimplyLinkedList(wxCommandEvent& e);
	void toDoublyLinkedList(wxCommandEvent& e);
	void toCircularLinkedList(wxCommandEvent& e);
	void toStack(wxCommandEvent& e);
	void toQueue(wxCommandEvent& e);
	void toGraph(wxCommandEvent& e);
	void toHashTable(wxCommandEvent& e);
	void toMaxHeap(wxCommandEvent& e);
};
