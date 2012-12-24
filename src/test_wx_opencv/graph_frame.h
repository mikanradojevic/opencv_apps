#ifndef __GRAPH_FRAME_H__
#define __GRAPH_FRAME_H__

#include <numeric>
#include "prerequisites.h"
#include "gui_classes.h" 
#include "mathplot.h" 

//////////////////////////////////////////////////////////////////////////

class c_graph_frame : public GraphFrame
{
public:
	c_graph_frame(wxWindow *parent, 
				mpFX *fx_layer, 
				wxWindowID id = wxID_ANY, 
				const wxString& title = wxEmptyString, 
				const wxPoint& pos = wxDefaultPosition, 
				const wxSize& size = wxSize( 500,300 ), 
				long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
	
	~c_graph_frame() {} 

	mpWindow* get_mp_window() { return m_mp_window; }
	
private: 
	
	mpWindow *m_mp_window; 
	mpInfoCoords *m_mp_info_coords; 
	
	DECLARE_EVENT_TABLE()
};


#endif