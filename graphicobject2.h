#pragma once

#include <wx/wx.h>
#include <vector>

struct GraphicObject2 {
	wxRect2DDouble rect;
	wxColor color;
	wxString text;
	wxAffineMatrix2D transform;
};
