#include "BstaticArray.h"

short a_size = 0;
int a[20];

void BstaticArray::addBox() {
	if (a_size == 0) {
		wxMessageBox(wxT("The maximum number of element you can have is 12"), wxT("Error"), wxICON_ERROR);
	}
}