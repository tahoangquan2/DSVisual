#include "receiver.h"
#include "UstaticArray.h"
#include "BstaticArray.h"
#include <time.h>

int getRandom(int l, int r) {
	return (rand() % (r - l + 1)) + l;
}

void drawBox(int pos, int value = -1000) {
	if (value == -1000) {
	}
}

void rGoToPanel(wxPanel* current_panel, wxPanel* goto_panel) {
	current_panel->Hide();
	goto_panel->Show();
}

void rClear(short id) {
	switch (id) {
	case 1:
		BstaticArray::a_size = 0;
		break;
	}
}

void rCreateRandom(short id) {
	srand(time(NULL));

	switch (id) {
	case 1:
		short random_size = getRandom(3, 12);
		for (int i = 1; i <= random_size; ++i) {
			if (BstaticArray::addBox()) {
				drawBox(i, BstaticArray::a[i]);
			}
			else {
				break;
			}
		}
		break;
	}
}
