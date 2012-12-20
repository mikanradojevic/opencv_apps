#ifndef __IMAGE_FRAME_H__
#define __IMAGE_FRAME_H__ 

#include <string>
#include <sstream>
#include "gui_classes.h"

class c_image_frame : public ImageFrame
{
public: 
	
	c_image_frame(wxWindow *parent, 
				wxWindowID id = wxID_ANY, 
				const wxString& title = wxEmptyString, 
				const wxPoint& pos = wxDefaultPosition, 
				const wxSize& size = wxSize( 500,300 ), 
				long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL); 
	
	~c_image_frame() {} 
	
	/// Menu Commands Handlers
	virtual void on_menu_open( wxCommandEvent& event );
	virtual void on_menu_exit( wxCommandEvent& event );
	virtual void on_erase_background( wxEraseEvent& event ) {}

	void open_image(const wxString& img_file);
	
private: 
	
};

#endif 