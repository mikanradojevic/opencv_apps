#include "image_frame.h"
#include "ocv_canvas.h"
#include "utils.h"
#include "wx/filedlg.h"
#include "overview_frame.h"

c_image_frame::c_image_frame(wxWindow *parent, 
							wxWindowID id, 
							const wxString& title, 
							const wxPoint& pos, 
							const wxSize& size,
							long style)
							: ImageFrame(parent, id, title, pos, size, style) 
							, m_is_rgb(false)
{ 
	
} 

void c_image_frame::set_image(ocv_mat_ptr image, const std::string& name, e_image_idx img_idx)
{ 
	if (is_image_valid(image))
	{
		m_img = image; 
		m_img_idx = img_idx; 
		m_ocv_canvas->set_image(image, "test");
		m_ocv_canvas->set_rgb(false); 
		m_ocv_canvas->set_thumbnail(false); 

		int w = image->cols;
		int h = image->rows;
		m_ocv_canvas->SetScrollbars(1, 1, w, h, 0, 0); 

		resize_window_image(w+20, h+20); 
	}
	
	Refresh(); 
}

void c_image_frame::resize_window_image(int width, int height)
{
	wxRect frame_rect = GetRect(); 
	wxRect client_rect = GetClientRect(); 
	wxSize other_size = wxSize((frame_rect.width - client_rect.width), (frame_rect.height - client_rect.height)); 
	wxSize image_size = wxSize(width, height); 
	SetSize(other_size + image_size); 
}

////////////////////////////////////////////////////////////////////////// 

void c_image_frame::on_size( wxSizeEvent& event )
{ 
	m_ocv_canvas->ClearBackground(); 
	Refresh(); 
	
	event.Skip();
}

void c_image_frame::on_paint( wxPaintEvent& event )
{
	super::on_paint(event);
}

void c_image_frame::on_leave_window( wxMouseEvent& event )
{
	
}

void c_image_frame::on_calc_mtf( wxCommandEvent& event )
{	
	if (m_ocv_canvas->is_line_ready())
	{
		wxPoint start = m_ocv_canvas->get_line_start();
		wxPoint end = m_ocv_canvas->get_line_end(); 

		m_overview_frame->get_overview_graph_panel_mtf()->calculate_mtf(m_img, m_img_idx, start, end); 
		m_overview_frame->get_overview_graph_panel_mtf()->Refresh(); 
		m_overview_frame->get_overview_graph_panel_mtf()->Update(); 
	}
	else 
	{
		wx_log_message("line is not ready");
	}
}

void c_image_frame::on_calc_histogram( wxCommandEvent& event )
{
	m_overview_frame->get_overview_graph_panel_hist()->calculate_histogram(m_img, m_img_idx);  
	m_overview_frame->get_overview_graph_panel_hist()->Refresh(); 
	m_overview_frame->get_overview_graph_panel_hist()->Update(); 
}