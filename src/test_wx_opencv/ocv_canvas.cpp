#include "wx/filedlg.h"

#include "ocv_canvas.h"
#include "utils.h"

BEGIN_EVENT_TABLE(c_ocv_canvas, wxScrolledWindow) 
	EVT_PAINT(c_ocv_canvas::on_paint) 
	// EVT_ERASE_BACKGROUND(c_ocv_canvas::on_erase_background) 
	EVT_SIZE(c_ocv_canvas::on_size)
	EVT_LEFT_DCLICK(c_ocv_canvas::on_left_dclick)			// Mouse left double-click 
END_EVENT_TABLE()
	
c_ocv_canvas::c_ocv_canvas(wxWindow *parent, 
	wxWindowID id /* = wxID_ANY */, 
	const wxPoint& pos /* = wxDefaultPosition */, 
	const wxSize& size /* = wxDefaultSize */, 
	long style /* = wxHSCROLL | wxVSCROLL */, 
	const wxString& name /* = "OpenCV Image" */)
	: wxScrolledWindow(parent, id, pos, size, style, name)
	, m_zoom_factor(1.0f)
	, m_draw_pos_x(0), m_draw_pos_y(0) 
	, m_img_index(k_left_image)
	, m_need_update(true)
	, m_is_thunmnail(true) 
	, m_img_loaded(false)
{
}

//////////////////////////////////////////////////////////////////////////
/// Events Handlers 
//////////////////////////////////////////////////////////////////////////

void c_ocv_canvas::on_paint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	PrepareDC(dc);

	if (m_need_update)
	{
		if (is_img_loaded())
		{
			ocv_mat_ptr img = get_ocv_img_mgr()->get_grayscale_img(m_img_index); 
			draw_cv_img(dc, img); 
		} 
		else 
		{
			draw_blank(dc);
		}
	}
	set_update_flag(false);
} 


void c_ocv_canvas::on_erase_background(wxEraseEvent& event)
{
}

void c_ocv_canvas::on_size(wxSizeEvent& event)
{
	if (m_is_thunmnail)
	{
		set_update_flag(true); 
	}
	else 
	{
		/*
		wxSize wnd_size = event.GetSize(); 
		int img_display_width = m_img_width * m_zoom_factor; 
		int img_display_height = m_img_height * m_zoom_factor; 
		m_draw_pos_x= (wxCoord)((wnd_size.x - img_display_width) * 0.5f); 
		m_draw_pos_y = (wxCoord)((wnd_size.y - img_display_height) * 0.5f);
		*/
	}

	// event.Skip(); 
	wxScrolledWindow::OnSize(event);

	wxSize wnd_size = GetSize(); 
	wxString str = wxT("ocv_canvas resized: "); 
	str << wnd_size.GetWidth(); 
	str << wxT(", ");
	str << wnd_size.GetHeight();
	wxLogDebug(str);
}

void c_ocv_canvas::on_left_dclick(wxMouseEvent& event)
{
	wxString wildcard_str; 
	wildcard_str += wxT("Image Files|*.jpg;*.tif|");
	wildcard_str += wxT("TIFF (*.tif)|*.tif|");
	wildcard_str += wxT("All Files (*.*)|*.*");

	wxString str; 
	str << wxT("Select image file to open!");  
	wxFileDialog *file_dlg = new wxFileDialog(this, 
		str, 
		wxEmptyString, 
		wxEmptyString, 
		wildcard_str, 
		wxFD_OPEN);

	if (file_dlg->ShowModal() == wxID_OK) 
	{
		open_image(file_dlg->GetPath()); 
	}  
}

////////////////////////////////////////////////////////////////////////// 

void c_ocv_canvas::open_image(const wxString& img_file)
{
	/// Load the image using the c_ocv_image_manager
	std::string file_name = wxstr_to_std(img_file);
	ocv_mat_ptr new_img = get_ocv_img_mgr()->load_from_file(file_name, m_img_index);

	bool err = !new_img->data;  
	// int err = m_ocv_canvas->load_image(img_file);
	if (err)
	{
		std::stringstream ss; 
		std::string err_str = wxstr_to_std(img_file);
		ss << "Open file FAILEd!" << " " << err_str;
		wx_log_error(ss.str().c_str()); 
	}
	else 
	{
		/*
		wxSize img_dimension = get_img_dimension();
		wxSize old_client_size = GetClientSize();
		wxSize offset = wxSize(std::max(img_dimension.GetWidth() - old_client_size.GetWidth(), 0), 
			std::max(img_dimension.GetHeight() - old_client_size.GetHeight(), 0));

		wxSize new_frame_size = wxSize(GetSize().GetWidth() + offset.GetWidth() + 10, GetSize().GetHeight() + offset.GetHeight() + 10);
		SetSize(new_frame_size); 
		SetMinSize(new_frame_size);
		SetMaxSize(new_frame_size);
		*/ 
	}
	
	Refresh(true);
}

bool c_ocv_canvas::is_img_loaded() const
{
	ocv_mat_ptr img = get_ocv_img_mgr()->get_grayscale_img(m_img_index); 
	return !img->empty() && (img->data); 
}

//////////////////////////////////////////////////////////////////////////
/// Draw Functions
//////////////////////////////////////////////////////////////////////////

void c_ocv_canvas::draw_cv_img(wxDC& dc, ocv_mat_ptr& ocv_img) 
{
	wxSize client_size = GetClientSize();
	cv::Size cv_size(client_size.GetWidth(), client_size.GetHeight());
	ocv_mat_ptr resized_img = get_ocv_img_mgr()->resize_img(m_img_index, cv_size); 

	/*
	imshow("Source Image", *(get_ocv_img_mgr()->get_grayscale_img(m_img_index))); 
	imshow("Dest Image", *resized_img);
	*/
	
	cv::Mat temp = resized_img->clone();
	cvtColor(*resized_img, temp, CV_GRAY2BGR); 
	wxImage wx_img(temp.cols, temp.rows, temp.data, true); 
	wxBitmap wx_bitmap(wx_img);
	
	// Draw the bitmap
	dc.DrawBitmap(wx_bitmap, 0, 0); 
}

void c_ocv_canvas::draw_blank(wxDC& dc)
{
	wxSize client_size = GetClientSize(); 

	dc.SetBrush(*wxLIGHT_GREY_BRUSH); 
	dc.DrawRectangle(0, 0, client_size.GetWidth(), client_size.GetHeight()); 
} 