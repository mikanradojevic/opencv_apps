#include "graph_canvas.h"

c_graph_canvas::c_graph_canvas(wxWindow *parent, 
							wxWindowID id, 
							const wxPoint &pos /* = wxDefaultPosition */, 
							const wxSize &size /* = wxDefaultSize */, 
							long flags /* = 0 */ )
	: mpWindow(parent, id, pos, size, flags) 
{
	
}

void c_graph_canvas::setup_hist_graph(hist_data_vec& hist_data)
{
	DelAllLayers(true, true); 
		
	c_histogram_layar *hist_layer = new c_histogram_layar(hist_data);
	double min_x = hist_layer->GetMinX(); 
	double max_x = hist_layer->GetMaxX(); 
	double min_y = hist_layer->GetMinY(); 
	double max_y = hist_layer->GetMaxY(); 

	/// Setup the graph
	wxFont graph_font(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	mpScaleX *axis_x = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, true, mpX_NORMAL);
	mpScaleY *axis_y = new mpScaleY(wxT("Y"), mpALIGN_LEFT, true); 
	axis_x->SetFont(graph_font);
	axis_y->SetFont(graph_font);
	axis_x->SetDrawOutsideMargins(false); 
	axis_y->SetDrawOutsideMargins(false);

	this->SetMargins(30, 10, 30, 60);
	this->AddLayer(axis_x);
	this->AddLayer(axis_y); 
	this->AddLayer(hist_layer); 

	this->EnableDoubleBuffer(true);
	this->Fit(min_x, max_x, min_y, max_y);
	this->UpdateAll(); 
}

void c_graph_canvas::setup_mtf_graph(mtf_data_vec& mtf_data)
{
	DelAllLayers(true, true); 

	c_mtf_layer *mtf_layer = new c_mtf_layer(mtf_data);
	double min_x = mtf_layer->GetMinX(); 
	double max_x = mtf_layer->GetMaxX(); 
	double min_y = mtf_layer->GetMinY(); 
	double max_y = mtf_layer->GetMaxY(); 

	/// Setup the graph
	wxFont graph_font(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	mpScaleX *axis_x = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, true, mpX_NORMAL);
	mpScaleY *axis_y = new mpScaleY(wxT("Y"), mpALIGN_LEFT, true); 
	axis_x->SetFont(graph_font);
	axis_y->SetFont(graph_font);
	axis_x->SetDrawOutsideMargins(false); 
	axis_y->SetDrawOutsideMargins(false);

	this->SetMargins(30, 10, 30, 60);
	this->AddLayer(axis_x);
	this->AddLayer(axis_y); 
	this->AddLayer(mtf_layer); 

	this->EnableDoubleBuffer(true);
	this->Fit(min_x, max_x, min_y, max_y); 
	this->UpdateAll(); 
}

