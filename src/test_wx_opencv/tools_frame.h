#pragma once 

#include "gui_classes.h"
#include "prerequisites.h"

class c_overview_frame; 
class c_tools_frame : public ToolsFrame
{
	typedef ToolsFrame super; 

public: 
	c_tools_frame(wxWindow* parent,
				c_overview_frame *overview_frame = NULL,
				wxWindowID id = wxID_ANY,
				const wxString& title = wxEmptyString, 
				const wxPoint& pos = wxDefaultPosition, 
				const wxSize& size = wxSize( 500,300 ), 
				long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);

	virtual void on_save_report( wxCommandEvent& event ); 
	
private:
	bool validate_input(); 
	wxString make_folder_name();
	int write_grayscale_imgs(const wxString& path); 
	int write_hist_graphs(const wxString& path);
	int write_mtf_graphs(const wxString& path);

	c_overview_frame *m_overview_frame;
};