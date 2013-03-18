#ifndef __IMAGE_FRAME_H__
#define __IMAGE_FRAME_H__ 

#include <string>
#include <sstream>
#include "gui_classes.h"
#include "prerequisites.h"
#include "image.h"

class c_overview_frame; 
class c_image_frame : public ImageFrame
{
	typedef ImageFrame super; 
public: 	
	c_image_frame(wxWindow *parent, 
				wxWindowID id = wxID_ANY, 
				const wxString& title = wxEmptyString, 
				const wxPoint& pos = wxDefaultPosition, 
				const wxSize& size = wxSize( 500,300 ), 
				long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL); 
	
	~c_image_frame() {} 
	
	void set_image(ocv_mat_ptr image, const std::string& name, e_image_idx img_idx);
	
	////////////////////////////////////////////////////////////////////////// 
	
protected:
	
	void resize_window_image(int width, int height); 
	virtual void on_leave_window( wxMouseEvent& event ); 
	virtual void on_size( wxSizeEvent& event );
	virtual void on_paint( wxPaintEvent& event ); 

	virtual void on_calc_histogram( wxCommandEvent& event );
	virtual void on_calc_mtf( wxCommandEvent& event ); 
	
private: 
	ocv_mat_ptr m_img;
	e_image_idx m_img_idx; 
	bool m_is_rgb; 

	c_overview_frame *m_overview_frame; 
};

#endif 