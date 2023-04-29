#pragma once
#include "constant.h"
#include <wx/wx.h>

namespace BstaticArray {
	short a_size = 0;
	int a[15];

	bool addBox() {
		if (a_size > 12) {
			wxMessageBox(wxT("The maximum number of element you can have is 12"), wxT("Error"), wxICON_ERROR);
			return false;
		}
		++a_size;
		a[a_size] = 0;
		return true;
	}

};