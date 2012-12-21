#ifndef __OVERVIEW_FRAME_H__
#define __OVERVIEW_FRAME_H__

#include "wx/log.h"
#include "gui_classes.h"
#include "image.h"

class c_overview_img_panel : public OverviewImgSubPanel
{
public:

	c_overview_img_panel(wxWindow *parent,  
						wxWindowID id = wxID_ANY,
						const wxPoint& pos = wxDefaultPosition, 
						const wxSize& size = wxDefaultSize, 
						long style = wxTAB_TRAVERSAL);
	
private:

	void open_image(const wxString& img_file);
	void draw_panel(wxDC& dc);

	bool m_img_loaded;  
};

class c_overview_graph_panel : public OverviewGraphSubPanel
{
public:
	
	c_overview_graph_panel(wxPanel *parent, 
						wxWindowID id = wxID_ANY,
						const wxPoint& pos = wxDefaultPosition, 
						const wxSize& size = wxDefaultSize, 
						long style = wxTAB_TRAVERSAL); 
};


//////////////////////////////////////////////////////////////////////////


class c_overview_frame : public OverviewFrame
{
public:

	c_overview_frame(wxWindow *parent, 
					wxWindowID id = wxID_ANY, 
					const wxString& title = wxEmptyString, 
					const wxPoint& pos = wxDefaultPosition, 
					const wxSize& size = wxSize( 500,300 ), 
					long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL); 

	virtual ~c_overview_frame(); 
	
protected:

private: 
	void init_config(); 
	void restore_config();
	void write_config();

	void add_image_sub_panel(const wxString& caption);
	void add_graph_sub_panel(const wxString& caption); 
	wxLogWindow *m_log_wnd; 
};


#endif