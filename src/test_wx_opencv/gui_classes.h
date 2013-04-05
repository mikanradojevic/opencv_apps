///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_CLASSES_H__
#define __GUI_CLASSES_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
class c_graph_canvas;
class c_ocv_cam_canvas;
class c_ocv_canvas;

#include <wx/scrolwin.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/notebook.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_CAM_CANVAS_LEFT 1000
#define wxID_BTN_CAPTURE_LEFT 1001
#define wxID_CAM_CANVAS_MID 1002
#define wxID_BTN_CAPTURE_MID 1003
#define wxID_CAM_CANVAS_RIGHT 1004
#define wxID_BTN_CAPTURE_RIGHT 1005

///////////////////////////////////////////////////////////////////////////////
/// Class ImageFrame
///////////////////////////////////////////////////////////////////////////////
class ImageFrame : public wxFrame 
{
	private:
	
	protected:
		c_ocv_canvas* m_ocv_canvas;
		wxMenuBar* mImageFrameMenuBar;
		wxMenu* mFileMenu;
		wxMenu* mViewMenu;
		wxMenu* mImageMenu;
		wxMenu* mToolsMenu;
		wxMenu* mHelpMenu;
		wxStatusBar* mImageFrameStatusBar;
		wxToolBar* mImageFrameToolBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_paint( wxPaintEvent& event ) { event.Skip(); }
		virtual void on_size( wxSizeEvent& event ) { event.Skip(); }
		virtual void on_leave_window( wxMouseEvent& event ) { event.Skip(); }
		virtual void on_menu_open( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_menu_exit( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_calc_mtf( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_calc_histogram( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ImageFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~ImageFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GraphFrame
///////////////////////////////////////////////////////////////////////////////
class GraphFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mGraphFrameMenuBar;
		wxMenu* mFileMenu;
		wxMenu* mHelpMenu;
		wxToolBar* mGraphFrameToolBar;
	
	public:
		
		GraphFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GraphFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class OverviewFrame
///////////////////////////////////////////////////////////////////////////////
class OverviewFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mOverviewFrameMenuBar;
		wxMenu* mFileMenu;
		wxMenu* mHelpMenu;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_save_report( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		OverviewFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~OverviewFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class OverviewImgSubPanel
///////////////////////////////////////////////////////////////////////////////
class OverviewImgSubPanel : public wxPanel 
{
	private:
	
	protected:
		c_ocv_canvas* m_img_canvas_left;
		c_ocv_canvas* m_img_canvas_mid;
		c_ocv_canvas* m_img_canvas_right;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_left_dbl_clk( wxMouseEvent& event ) { event.Skip(); }
		virtual void on_paint( wxPaintEvent& event ) { event.Skip(); }
		virtual void on_left_img_thunmnail_double_click( wxMouseEvent& event ) { event.Skip(); }
		virtual void on_mid_img_thunmnail_double_click( wxMouseEvent& event ) { event.Skip(); }
		virtual void on_right_img_thunmnail_double_click( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		OverviewImgSubPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxRAISED_BORDER|wxSIMPLE_BORDER|wxSTATIC_BORDER|wxSUNKEN_BORDER|wxTAB_TRAVERSAL ); 
		~OverviewImgSubPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class OverviewGraphSubPanel 
///////////////////////////////////////////////////////////////////////////////
class OverviewGraphSubPanel  : public wxPanel 
{
	private:
	
	protected:
		c_graph_canvas* m_graph_wnd_left;
		c_graph_canvas* m_graph_wnd_mid;
		c_graph_canvas* m_graph_wnd_right;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_paint( wxPaintEvent& event ) { event.Skip(); }
		
	
	public:
		
		OverviewGraphSubPanel ( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~OverviewGraphSubPanel ();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class OverviewVideoSubPanel
///////////////////////////////////////////////////////////////////////////////
class OverviewVideoSubPanel : public wxPanel 
{
	private:
	
	protected:
		c_ocv_cam_canvas* m_cam_canvas_left;
		wxButton* m_btn_open_cam_left;
		wxButton* m_btn_capture_left;
		c_ocv_cam_canvas* m_cam_canvas_mid;
		wxButton* m_btn_open_cam_mid;
		wxButton* m_btn_capture_mid;
		c_ocv_cam_canvas* m_cam_canvas_right;
		wxButton* m_btn_open_cam_right;
		wxButton* m_btn_capture_right;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_open_cam_left_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_capture_left_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_open_cam_mid_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_capture_mid_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_open_cam_right_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_capture_right_click( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		OverviewVideoSubPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~OverviewVideoSubPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ToolsFrame
///////////////////////////////////////////////////////////////////////////////
class ToolsFrame : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* m_notebook;
		wxPanel* m_save_page;
		wxStaticText* m_static_project;
		wxTextCtrl* m_text_project;
		wxStaticText* m_static_lens_name;
		wxTextCtrl* m_txt_lens_name;
		wxStaticText* m_static_rotation;
		wxTextCtrl* m_text_rotation;
		wxButton* m_btn_save;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_save_report( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ToolsFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE );
		
		~ToolsFrame();
	
};

#endif //__GUI_CLASSES_H__
