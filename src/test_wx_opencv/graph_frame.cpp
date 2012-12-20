#include "graph_frame.h"

BEGIN_EVENT_TABLE(c_graph_frame, GraphFrame) 
END_EVENT_TABLE()

c_graph_frame::c_graph_frame(wxWindow *parent,
							mpFX *fx_layer, 
							wxWindowID id, 
							const wxString& title, 
							const wxPoint& pos, 
							const wxSize& size,
							long style) 
							: GraphFrame(parent, id, title, pos, size, style)
{
	assert(fx_layer);
	
	// Create the mathplot window
	wxFont label_font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL); 
	m_mp_window = new mpWindow(this, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);

	// Setup the axis layer 
	mpScaleX *x_axis = new mpScaleX(wxT("Grayscale"), mpALIGN_BOTTOM, true, mpX_NORMAL); 
	mpScaleY *y_axis = new mpScaleY(wxT("Pixels"), mpALIGN_LEFT, true);
	x_axis->SetFont(label_font); 
	y_axis->SetFont(label_font); 
	x_axis->SetDrawOutsideMargins(false); 
	y_axis->SetDrawOutsideMargins(false); 

	// Setup info coords layer
	m_mp_info_coords = new mpInfoCoords(wxRect(80, 20, 10, 10), wxTRANSPARENT_BRUSH);
	m_mp_info_coords->SetVisible(true); 

	// Add the layers to mpWindow
	m_mp_window->AddLayer(x_axis); 
	m_mp_window->AddLayer(y_axis); 
	m_mp_window->AddLayer(fx_layer);

	// Add mpWindow to the sizer
	GetSizer()->Add(m_mp_window, wxSizerFlags().Expand().Border(wxALL)); 
	SetAutoLayout(true); 

	m_mp_window->SetMargins(30, 30, 50, 100); 
	m_mp_window->EnableDoubleBuffer(true); 
	m_mp_window->SetMPScrollbars(false); 
	m_mp_window->Fit(fx_layer->GetMinX(), fx_layer->GetMaxX(), fx_layer->GetMinY(), fx_layer->GetMaxY()); 

} 