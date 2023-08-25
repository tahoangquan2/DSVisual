#include "Umain.h"
#include "receiver.h"
#include "Umenu.h"
#include "Usetting.h"
#include "UstaticArray.h"
#include "UdynamicArray.h"
#include "UsimplyLinkedList.h"
#include "UdoublyLinkedList.h"
#include "UcircularLinkedList.h"
#include "Ustack.h"
#include "Uqueue.h"
#include "graph.h"
#include "hashTable.h"

// UI for the main frame
Umain::Umain(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxIcon icon("assets/icon.jpg", wxBITMAP_TYPE_JPEG);
	SetIcon(icon);
	base->SetSize(size1, size2);

	Umenu* u_menu = new Umenu(base);
	u_menu->SetSize(size1, size2);
	u_menu->Show();

	Usetting* u_setting = new Usetting(base);
	u_setting->SetSize(size1, size2);
	u_setting->Hide();

	UstaticArray* u_static_array = new UstaticArray(base);
	u_static_array->SetSize(size1, size2);
	u_static_array->Hide();

	UdynamicArray* u_dynamic_array = new UdynamicArray(base);
	u_dynamic_array->SetSize(size1, size2);
	u_dynamic_array->Hide();

	UsimplyLinkedList* u_simply_linked_list = new UsimplyLinkedList(base);
	u_simply_linked_list->SetSize(size1, size2);
	u_simply_linked_list->Hide();

	UdoublyLinkedList* u_doubly_linked_list = new UdoublyLinkedList(base);
	u_doubly_linked_list->SetSize(size1, size2);
	u_doubly_linked_list->Hide();

	UcircularLinkedList* u_circular_linked_list = new UcircularLinkedList(base);
	u_circular_linked_list->SetSize(size1, size2);
	u_circular_linked_list->Hide();

	Ustack* u_stack = new Ustack(base);
	u_stack->SetSize(size1, size2);
	u_stack->Hide();

	Uqueue* u_queue = new Uqueue(base);
	u_queue->SetSize(size1, size2);
	u_queue->Hide();

	graph* u_graph = new graph(base);
	u_graph->SetSize(size1, size2);
	u_graph->Hide();

	hashTable* u_hash_table = new hashTable(base);
	u_hash_table->SetSize(size1, size2);
	u_hash_table->Hide();

	u_setting->parent = u_menu;
	u_static_array->parent = u_menu;
	u_dynamic_array->parent = u_menu;
	u_simply_linked_list->parent = u_menu;
	u_doubly_linked_list->parent = u_menu;
	u_circular_linked_list->parent = u_menu;
	u_stack->parent = u_menu;
	u_queue->parent = u_menu;
	u_graph->parent = u_menu;
	u_hash_table->parent = u_menu;
	u_menu->parent_setting = u_setting;
	u_menu->parent_static_array = u_static_array;
	u_menu->parent_dynamic_array = u_dynamic_array;
	u_menu->parent_simply_linked_list = u_simply_linked_list;
	u_menu->parent_doubly_linked_list = u_doubly_linked_list;
	u_menu->parent_circular_linked_list = u_circular_linked_list;
	u_menu->parent_stack = u_stack;
	u_menu->parent_queue = u_queue;
	u_menu->parent_graph = u_graph;
	u_menu->parent_hash_table = u_hash_table;

}
