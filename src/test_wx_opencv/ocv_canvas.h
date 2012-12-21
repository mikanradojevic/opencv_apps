#ifndef __OCV_CANVAS__
#define __OCV_CANVAS__

#include "wx/wx.h" 
#include "wx/dcbuffer.h"
#include "prerequisites.h"
#include "image.h"

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
		const wxSize& size = wxDefaultSize, 
		long style = wxHSCROLL | wxVSCROLL, 
		const wxString& name = _T("OpenCV Image")); 
	 
	/// Drawing methods
	void draw_cv_img(wxDC& dc, ocv_mat_ptr& ocv_img); 
	void draw_blank(wxDC& dc); 

	void set_img_idx(e_image_idx img_idx) { m_img_index = img_idx; }
	void set_thumbnail_flag(bool is_thunmnail) { m_is_thunmnail = is_thunmnail; set_update_flag(true); }
	void set_update_flag(bool need_update) { m_need_update = need_update; }

	e_image_idx get_img_idx() const { return m_img_index; }
	bool need_update() const { return m_need_update; }
	bool is_thunmnail() const { return m_is_thunmnail; }
	bool is_img_loaded() const;

protected:

	virtual void on_paint(wxPaintEvent& event);
	virtual void on_erase_background(wxEraseEvent& event);
	virtual void on_size(wxSizeEvent& event);  
	virtual void on_left_dclick(wxMouseEvent& event);

	void open_image(const wxString& img_file); 
	
private: 
	
	/// Image Index
	e_image_idx m_img_index; 

	/// View 
	float m_zoom_factor; 
	wxCoord m_draw_pos_x, m_draw_pos_y; 

	/// Flags 
	bool m_need_update; 
	bool m_is_thunmnail;
	bool m_img_loaded; 

	DECLARE_EVENT_TABLE() 
};

#endif