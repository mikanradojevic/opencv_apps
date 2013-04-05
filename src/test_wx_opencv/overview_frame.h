#ifndef __OVERVIEW_FRAME_H__
#define __OVERVIEW_FRAME_H__

#include "wx/log.h"
#include "gui_classes.h"
#include "prerequisites.h"
#include "image.h"
#include "graph.h"

class c_overview_frame;

class c_overview_cam_panel : public OverviewVideoSubPanel
{
public: 
	c_overview_cam_panel(wxWindow *parent,  
						wxWindowID id = wxID_ANY,
						const wxPoint& pos = wxDefaultPosition, 
						const wxSize& size = wxDefaultSize, 
						long style = wxTAB_TRAVERSAL); 	

	virtual void on_open_cam_left_click( wxCommandEvent& event );
	virtual void on_open_cam_mid_click( wxCommandEvent& event ); 
	virtual void on_open_cam_right_click( wxCommandEvent& event ); 
	
	virtual void on_capture_left_click( wxCommandEvent& event ); 
	virtual void on_capture_mid_click( wxCommandEvent& event );
	virtual void on_capture_right_click( wxCommandEvent& event );

	void close_all_cams(); 

private: 
	c_overview_frame *m_overview_frame; 

	int m_rotation_angle; 


};

//////////////////////////////////////////////////////////////////////////

class c_overview_img_panel : public OverviewImgSubPanel
{
public:

	c_overview_img_panel(wxWindow *parent,  
						wxWindowID id = wxID_ANY,
						const wxPoint& pos = wxDefaultPosition, 
						const wxSize& size = wxDefaultSize, 
						long style = wxTAB_TRAVERSAL);
	
	c_ocv_canvas* get_ocv_canvas(e_image_idx img_idx);

	virtual void on_left_img_thunmnail_double_click( wxMouseEvent& event); 
	virtual void on_mid_img_thunmnail_double_click( wxMouseEvent& event ); 
	virtual void on_right_img_thunmnail_double_click( wxMouseEvent& event ); 

private:
	c_overview_frame *m_overview_frame; 
}; 

//////////////////////////////////////////////////////////////////////////

class c_overview_graph_panel : public OverviewGraphSubPanel
{
public:
	
	c_overview_graph_panel(wxWindow *parent, 
						e_graph_type graph_type, 
						const wxString& title = wxT("Graphs"), 
						wxWindowID id = wxID_ANY,
						const wxPoint& pos = wxDefaultPosition, 
						const wxSize& size = wxDefaultSize, 
						long style = wxTAB_TRAVERSAL); 
	
	void update_graph(); 
	void on_img_loaded(wxEvent& event); 
	void calculate_histogram(ocv_mat_ptr img, e_image_idx img_idx);
	void calculate_mtf(ocv_mat_ptr img, e_image_idx img_idx, wxPoint& start, wxPoint& end); 
	void set_label_text(const wxString& label); 

	c_graph_canvas* get_left_graph_canvas() { return m_graph_wnd_left; }
	c_graph_canvas* get_mid_graph_canvas() { return m_graph_wnd_mid; }
	c_graph_canvas* get_right_graph_canvas() { return m_graph_wnd_right; }

private:
	e_graph_type m_graph_type; 
	
	DECLARE_EVENT_TABLE()
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
	
	c_overview_cam_panel* get_overview_cam_panel();
	c_overview_img_panel* get_overview_img_panel(); 
	c_overview_graph_panel* get_overview_graph_panel_hist();
	c_overview_graph_panel* get_overview_graph_panel_mtf(); 
	
	virtual void on_save_report( wxCommandEvent& event ); 


	std::string m_current_left_grayscale_img_name;
	std::string m_current_mid_grayscale_img_name;
	std::string m_current_right_grayscale_img_name;
	
private: 
	void init_config(); 
	void restore_config();
	void write_config();

	void add_cam_sub_panel(const wxString& caption); 
	void add_image_sub_panel(const wxString& caption);
	void add_graph_sub_panel(const wxString& caption, e_graph_type graph_type); 

	wxString generate_dir_name();

	wxLogWindow *m_log_wnd; 
};


#endif