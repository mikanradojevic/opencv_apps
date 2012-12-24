#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <algorithm>
#include "prerequisites.h"
#include "mathplot.h"

enum e_graph_type
{
	k_graph_histogram = 0, 
	k_graph_mtf
};

class c_histogram_layar : public mpFX
{
public: 
	c_histogram_layar(hist_data_vec& hist_data)
		: mpFX(wxT("histogram figure"), mpALIGN_LEFT)
		, m_hist_data(hist_data)
	{
		m_max_y = *std::max_element(hist_data.begin(), hist_data.end());
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

#endif