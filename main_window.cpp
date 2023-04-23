#include "main_window.h"
#include "./ui_main_window.h"

main_window::main_window(QWidget *parent): QMainWindow(parent), uiMenu(new Ui::main_window) {
	uiMenu->setupUi(this);
}

main_window::~main_window() {
	delete uiMenu;
}
