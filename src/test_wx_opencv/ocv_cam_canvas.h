#ifndef __OCV_CAM_CANVAS_H__
#define __OCV_CAM_CANVAS_H__

#include "ocv_canvas.h"

class c_render_timer; 
class c_ocv_cam_canvas : public c_ocv_canvas
{
	typedef c_ocv_canvas super; 
	
public:
	c_ocv_cam_canvas(wxWindow *parent, 
		wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, 
		long style = wxHSCROLL | wxVSCROLL, 
		const wxString& name = _T("OpenCV Camera")); 
	
	~c_ocv_cam_canvas(); 

	int get_videocap_idx() const { return m_videocap_idx; }
	void set_videocap_idx(e_image_idx videocap_idx) { m_videocap_idx = videocap_idx; }
	void active_render_loop(bool on);

	ocv_mat_ptr get_current_frame(); 
	
protected: 

	virtual void on_paint(wxPaintEvent& event);
	virtual void on_idle(wxIdleEvent& event);
	void draw_now();
	virtual void draw_captured(wxDC& dc); 

private: 
	// The index of the OpenCV video capture
	e_image_idx m_videocap_idx; 

	// Rendering Timer 
	c_render_timer *m_render_timer; 

	// Current frame of image from camera 
	ocv_mat_ptr m_current_frame; 
	
	bool m_render_loop_on;
	
	DECLARE_EVENT_TABLE() 
};


#endif