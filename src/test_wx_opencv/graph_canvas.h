#ifndef __GRAPH_CANVAS_H__
#define __GRAPH_CANVAS_H__

#include "mathplot.h"
#include "wx/wx.h"
#include "graph.h" 

class c_graph_canvas : public mpWindow
{
public: 
	
	c_graph_canvas(wxWindow *parent, 
				wxWindowID id,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				long flags = 0 );
	

	void setup_hist_graph(hist_data_vec& hist_data);
	void setup_mtf_graph(mtf_data_vec& mtf_data); 

	
};



#endif