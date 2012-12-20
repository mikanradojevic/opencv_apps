#ifndef __GRAPH_FRAME_H__
#define __GRAPH_FRAME_H__

#include <numeric>
#include "prerequisites.h"
#include "gui_classes.h" 
#include "mathplot.h"

class c_histogram_layar : public mpFX
{
public: 
	c_histogram_layar(hist_data_vec& hist_data)
		: mpFX(wxT("histogram figure"), mpALIGN_LEFT)
		, m_hist_data(hist_data)
	{
		m_max_y = std::accumulate(m_hist_data.begin(), m_hist_data.end(), 0); 
	}
	
	virtual double GetY(double x) 
	{
		unsigned int _x = (unsigned int)x;
		if (_x < m_hist_data.size())
			return (double)m_hist_data[_x]; 
		else 
			return 0; 
	} 

	virtual double GetMinX() 
	{
		return 0; 
	}

	virtual double GetMaxX() 
	{
		return (double)m_hist_data.size(); 
	}

	virtual double GetMinY()
	{
		return 0; 
	}

	virtual double GetMaxY() 
	{
		return m_max_y; 
	}

private:
	hist_data_vec m_hist_data;  
	int m_max_y; 
};

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