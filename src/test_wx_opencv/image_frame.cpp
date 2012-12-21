#include "image_frame.h"
#include "ocv_canvas.h"
#include "utils.h"
#include "wx/filedlg.h"

c_image_frame::c_image_frame(wxWindow *parent, 
							wxWindowID id, 
							const wxString& title, 
							const wxPoint& pos, 
							const wxSize& size,
							long style)
							: ImageFrame(parent, id, title, pos, size, style) 
{ 

}


void c_image_frame::on_menu_open( wxCommandEvent& event )
{ 
	wxString wildcard_str; 
	wildcard_str += wxT("Image Files|*.jpg;*.tif|");
	wildcard_str += wxT("TIFF (*.tif)|*.tif|");
	wildcard_str += wxT("All Files (*.*)|*.*");

	wxFileDialog *file_dlg = new wxFileDialog(this, wxT("Select image file to open!"), wxEmptyString, wxEmptyString, wildcard_str, wxFD_OPEN); 
	if (file_dlg->ShowModal() == wxID_OK)
	{
		open_image(file_dlg->GetPath()); 
	}
}

void c_image_frame::on_menu_exit( wxCommandEvent& event )
{ 
	
}

void c_image_frame::open_image(const wxString& img_file)
{
	/*
	int err = m_ocv_canvas->load_image(img_file);
	if (err)
	{
		std::stringstream ss; 
		std::string err_str = wxstr_to_std(img_file);
		ss << "Open file FAILEd!" << " " << err_str;
		wx_log_error(ss.str().c_str());
	}
	else 
	{
		wxSize img_dimension = m_ocv_canvas->get_img_dimension();
		wxSize old_client_size = GetClientSize();
		wxSize offset = wxSize(std::max(img_dimension.GetWidth() - old_client_size.GetWidth(), 0), 
							std::max(img_dimension.GetHeight() - old_client_size.GetHeight(), 0));

		wxSize new_frame_size = wxSize(GetSize().GetWidth() + offset.GetWidth() + 10, GetSize().GetHeight() + offset.GetHeight() + 10);
		SetSize(new_frame_size); 
		SetMinSize(new_frame_size);
		SetMaxSize(new_frame_size);
	}
	*/
}
 

