#pragma once
#include "constant.h"
#include <wx/wx.h>

namespace BstaticArray {
	short a_size = 0;
	int a[15];

	bool addBox(int value = 0) {
		if (a_size == max_size) {
			wxMessageBox(wxT("The maximum number of element you can have is 12"), wxT("Error"), wxICON_ERROR);
			return false;
		}
		++a_size;
		a[a_size] = value;
		return true;
	}

};