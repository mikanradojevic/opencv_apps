#include "wx/filedlg.h"

#include "ocv_canvas.h"
#include "utils.h"

BEGIN_EVENT_TABLE(c_ocv_canvas, wxScrolledWindow) 
	EVT_PAINT(c_ocv_canvas::on_paint) 
	EVT_SIZE(c_ocv_canvas::on_size)
	EVT_LEFT_DCLICK(c_ocv_canvas::on_left_dclick)			// Mouse left double-click 
	EVT_LEFT_UP(c_ocv_canvas::on_left_up)
	EVT_LEFT_DOWN(c_ocv_canvas::on_left_down)
	EVT_MOTION(c_ocv_canvas::on_motion)
END_EVENT_TABLE()

/// Custom event type
DEFINE_EVENT_TYPE(wxEVT_IMG_LOADED_CMD)

//////////////////////////////////////////////////////////////////////////

c_ocv_canvas::c_ocv_canvas(wxWindow *parent, 
	wxWindowID id /* = wxID_ANY */, 
	const wxPoint& pos /* = wxDefaultPosition */, 
	const wxSize& size /* = wxDefaultSize */, 
	long style /* = wxHSCROLL | wxVSCROLL */, 
	const wxString& name /* = "OpenCV Image" */)
	: wxScrolledWindow(parent, id, pos, size, style, name)
	, m_is_thumbnail(true)
	, m_update(true)
	, m_draw_line(false)
	, m_using_line_tool(false)
{
}

void c_ocv_canvas::set_image(ocv_mat_ptr image, const std::string& name) 
{
	m_img = image; 
	m_name = name;
	m_update = true;

	Refresh(); 
	Update(); 
}

//////////////////////////////////////////////////////////////////////////
/// Events Handlers 
//////////////////////////////////////////////////////////////////////////

void c_ocv_canvas::on_paint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	PrepareDC(dc);

	if (m_update && is_image_valid(m_img))
	{
		draw_cv_img(dc, m_img);
		m_update = false;
	} 
	else if (is_image_valid(m_img))
	{
		draw_blank(dc); 
	}

	draw_line(dc); 
} 


void c_ocv_canvas::on_erase_background(wxEraseEvent& event)
{
}

void c_ocv_canvas::on_size(wxSizeEvent& event)
{
	/*
	m_update = true; 

	// event.Skip(); 
	wxScrolledWindow::OnSize(event);

	wxSize wnd_size = GetSize(); 
	wxString str = wxT("ocv_canvas resized: "); 
	str << wnd_size.GetWidth(); 
	str << wxT(", ");
	str << wnd_size.GetHeight();
	wxLogDebug(str); 
	*/

	m_update = true; 
	wxScrolledWindow::OnSize(event);
	// event.Skip(); 
}

void c_ocv_canvas::on_left_dclick(wxMouseEvent& event)
{ 
} 

void c_ocv_canvas::on_left_down( wxMouseEvent& event )
{
	wxPoint pt = event.GetPosition(); 
	wxRect client_rect = GetClientRect(); 

	if (pt.x < client_rect.width && pt.y < client_rect.height) 
	{
		wxLogMessage(wxT("mouse down")); 
		m_line_start = pt; 
		m_using_line_tool = true; 
		m_draw_line = false; 
	}
}

void c_ocv_canvas::on_left_up( wxMouseEvent& event ) 
{	
	wxPoint pt = event.GetPosition(); 
	wxRect client_rect = GetClientRect(); 

	if (pt.x < client_rect.width && pt.y < client_rect.height) 
	{
		wxLogMessage(wxT("mouse up")); 
		m_line_end = pt; 
		m_using_line_tool = false; 
		m_draw_line = true; 
		Update(); 
	}
}

void c_ocv_canvas::on_motion(wxMouseEvent& event)
{
	wxPoint pt = event.GetPosition(); 
	wxRect client_rect = GetClientRect(); 

	if (pt.x < client_rect.width && pt.y < client_rect.height) 
	{ 
		wxLogMessage(wxT("mouse motion")); 
		m_current_mouse_pt = pt; 
		if (m_using_line_tool) 
		{
			m_update = true; 
			Refresh();
			Update(); 
		}
	}
}

//////////////////////////////////////////////////////////////////////////
/// Draw Functions
//////////////////////////////////////////////////////////////////////////

void c_ocv_canvas::draw_cv_img(wxDC& dc, ocv_mat_ptr& ocv_img) 
{ 
	cv::Mat temp;
	cv::Mat resized_img;
	if (m_is_thumbnail) 
	{
		wxSize client_size = GetClientSize();
		cv::Size cv_size(client_size.GetWidth(), client_size.GetHeight());
		ocv_mat_ptr resized_img = resize_image(m_img, cv_size); 
		temp = resized_img->clone(); 
		if (m_is_rgb) 
		{ 
			cvtColor(*resized_img, temp, CV_RGB2BGR); 
		} 
		else 
		{
			cvtColor(*m_img, temp, CV_GRAY2BGR);
		}
	}
	else
	{
		if (m_is_rgb) 
		{ 
			cvtColor(*m_img, temp, CV_RGB2BGR); 
		} 
		else 
		{
			cvtColor(*m_img, temp, CV_GRAY2BGR); 
		}
	}
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

void c_ocv_canvas::draw_line(wxDC& dc)
{
	if (m_using_line_tool)
	{
		//wxLogMessage(wxT("drawing")); 
		dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
		dc.DrawLine(m_line_start, m_current_mouse_pt);  
	}

	if (m_draw_line) 
	{
		dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
		dc.DrawLine(m_line_start, m_line_end); 
	}
}
