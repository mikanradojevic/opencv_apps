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
	
	void set_image(ocv_mat_ptr image, const std::string& name); 
	void show_image();
	
	void set_rgb(bool flag) { m_is_rgb = flag; }
	void set_thumbnail(bool flag) { m_is_thumbnail = flag; } 

	bool is_line_ready() const { return m_draw_line; }
	wxPoint get_line_start() const { return m_line_start; }
	wxPoint get_line_end() const { return m_line_end; }

protected:
	void draw_blank(wxDC& dc); 
	void draw_cv_img(wxDC& dc, ocv_mat_ptr& ocv_img); 
	void draw_line(wxDC& dc);

	virtual void on_paint(wxPaintEvent& event);
	virtual void on_erase_background(wxEraseEvent& event);
	virtual void on_size(wxSizeEvent& event);  
	virtual void on_left_dclick(wxMouseEvent& event);
	virtual void on_left_down( wxMouseEvent& event ); 
	virtual void on_left_up( wxMouseEvent& event ); 
	virtual void on_motion(wxMouseEvent& event);


private:
	/// The image to be drawn
	ocv_mat_ptr m_img; 
	std::string m_name; 
	
	/// Flags
	bool m_is_thumbnail;
	bool m_is_rgb; 
	bool m_update; 

	bool m_using_line_tool; 
	bool m_draw_line; 
	wxPoint m_line_start, m_line_end;
	wxPoint m_current_mouse_pt;  

	DECLARE_EVENT_TABLE() 
};

#endif