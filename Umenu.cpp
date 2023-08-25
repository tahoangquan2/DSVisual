#include "Umenu.h"
#include "receiver.h"
#include "Umain.h"

// main page for the UI menu
Umenu::Umenu(wxPanel* parent) : wxPanel(parent) {
	base->SetSize(size1, size2);
	srand(time(NULL));

	//wxButton* button_to_setting = new wxButton(base, wxID_ANY, "Setting", wxPoint(100, 50), wxSize(200, 50));
	wxButton* button_to_static_array = new wxButton(base, wxID_ANY, "Static Array", wxPoint(150, 120), wxSize(200, 50));
	wxButton* button_to_dynamic_array = new wxButton(base, wxID_ANY, "Dynamic Array", wxPoint(150, 180), wxSize(200, 50));
	wxButton* button_to_simply_linked_list = new wxButton(base, wxID_ANY, "Simply Linked List", wxPoint(150, 240), wxSize(200, 50));
	wxButton* button_to_doubly_linked_list = new wxButton(base, wxID_ANY, "Doubly Linked List", wxPoint(150, 300), wxSize(200, 50));
	wxButton* button_to_circular_linked_list = new wxButton(base, wxID_ANY, "Circular Linked List", wxPoint(150, 360), wxSize(200, 50));
	wxButton* button_to_stack = new wxButton(base, wxID_ANY, "Stack", wxPoint(150, 420), wxSize(200, 50));
	wxButton* button_to_queue = new wxButton(base, wxID_ANY, "Queue", wxPoint(150, 480), wxSize(200, 50));

	wxButton* button_to_graph = new wxButton(base, wxID_ANY, "Graph", wxPoint(400, 120), wxSize(200, 50));
	wxButton* button_to_hash_table = new wxButton(base, wxID_ANY, "Hash Table", wxPoint(400, 180), wxSize(200, 50));
	wxButton* button_to_max_heap = new wxButton(base, wxID_ANY, "Max Heap", wxPoint(400, 240), wxSize(200, 50));

	//button_to_setting->Bind(wxEVT_BUTTON, &Umenu::toSetting, this);
	button_to_static_array->Bind(wxEVT_BUTTON, &Umenu::toStaticArray, this);
	button_to_dynamic_array->Bind(wxEVT_BUTTON, &Umenu::toDynamicArray, this);
	button_to_simply_linked_list->Bind(wxEVT_BUTTON, &Umenu::toSimplyLinkedList, this);
	button_to_doubly_linked_list->Bind(wxEVT_BUTTON, &Umenu::toDoublyLinkedList, this);
	button_to_circular_linked_list->Bind(wxEVT_BUTTON, &Umenu::toCircularLinkedList, this);
	button_to_stack->Bind(wxEVT_BUTTON, &Umenu::toStack, this);
	button_to_queue->Bind(wxEVT_BUTTON, &Umenu::toQueue, this);

	button_to_graph->Bind(wxEVT_BUTTON, &Umenu::toGraph, this);
	button_to_hash_table->Bind(wxEVT_BUTTON, &Umenu::toHashTable, this);
	button_to_max_heap->Bind(wxEVT_BUTTON, &Umenu::toMaxHeap, this);
}

// go to setting
void Umenu::toSetting(wxCommandEvent& e) {
	rGoToPanel(this, parent_setting);
}

// go to static array
void Umenu::toStaticArray(wxCommandEvent& e) {
	rGoToPanel(this, parent_static_array);
}

// go to dynamic array
void Umenu::toDynamicArray(wxCommandEvent& e) {
	rGoToPanel(this, parent_dynamic_array);
}

// go to simply linked list
void Umenu::toSimplyLinkedList(wxCommandEvent& e) {
	rGoToPanel(this, parent_simply_linked_list);
}

// go to doubly linked list
void Umenu::toDoublyLinkedList(wxCommandEvent& e) {
	rGoToPanel(this, parent_doubly_linked_list);
}

// go to circular linked list
void Umenu::toCircularLinkedList(wxCommandEvent& e) {
	rGoToPanel(this, parent_circular_linked_list);
}

// go to stack
void Umenu::toStack(wxCommandEvent& e) {
	rGoToPanel(this, parent_stack);
}

// go to queue
void Umenu::toQueue(wxCommandEvent& e) {
	rGoToPanel(this, parent_queue);
}

// go to graph
void Umenu::toGraph(wxCommandEvent& e) {
	rGoToPanel(this, parent_graph);
}

// go to hash table
void Umenu::toHashTable(wxCommandEvent& e) {
	rGoToPanel(this, parent_hash_table);
}

// go to max heap
void Umenu::toMaxHeap(wxCommandEvent& e) {
	rGoToPanel(this, parent_max_heap);
}
