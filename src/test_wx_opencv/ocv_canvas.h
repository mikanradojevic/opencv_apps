#ifndef __OCV_CANVAS__
#define __OCV_CANVAS__

#include "wx/wx.h" 
#include "wx/dcbuffer.h"
#include "prerequisites.h"

enum e_img_mode
{
	k_img_rgb = 0, 
	k_img_grayscale = 1
};

class c_ocv_canvas : public wxScrolledWindow
{
	typedef wxScrolledWindow super; 
	
public: 
	c_ocv_canvas(wxWindow *parent, 
		wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxSize(10, 10), 
		long style = wxHSCROLL | wxVSCROLL, 
		const wxString& name = _T("OpenCV Image")); 
	
	virtual void on_init();
	virtual void on_paint(wxPaintEvent& event);
	virtual void on_erase_background(wxEraseEvent& event);
	virtual void on_size(wxSizeEvent& event); 

	int load_image(const wxString& img_file);
	void unload_image(); 
	bool is_current_valid() const; 
	void draw_cv_img(wxDC& dc, ocv_mat_ptr& ocv_img); 
	void draw_blank(wxDC& dc); 

	void set_img_mode(e_img_mode mode) {m_img_mode = mode;}
	e_img_mode get_img_mode() const { return m_img_mode; }
	wxSize get_img_dimension() const { return wxSize(m_img_width, m_img_height); }

private: 
	 
	/// Image Data
	ocv_mat_ptr m_ocv_org_img; 
	ocv_mat_ptr m_ocv_gray;	
	// wxbitmap_ptr m_wx_bitmap; 
	
	/// Image Properties
	wxString m_img_path; 
	int m_img_size;
	int m_img_width, m_img_height; 
	int m_img_bpp; 

	/// View 
	float m_zoom_factor; 
	wxCoord m_draw_pos_x, m_draw_pos_y; 
	e_img_mode m_img_mode;

	DECLARE_EVENT_TABLE() 
};

#endif