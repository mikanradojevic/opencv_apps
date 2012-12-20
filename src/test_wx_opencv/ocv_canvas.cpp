#include "ocv_canvas.h"
#include "utils.h"

BEGIN_EVENT_TABLE(c_ocv_canvas, wxScrolledWindow) 
	EVT_PAINT(c_ocv_canvas::on_paint) 
	// EVT_ERASE_BACKGROUND(c_ocv_canvas::on_erase_background) 
	EVT_SIZE(c_ocv_canvas::on_size)
END_EVENT_TABLE()
	
c_ocv_canvas::c_ocv_canvas(wxWindow *parent, 
	wxWindowID id /* = wxID_ANY */, 
	const wxPoint& pos /* = wxDefaultPosition */, 
	const wxSize& size /* = wxDefaultSize */, 
	long style /* = wxHSCROLL | wxVSCROLL */, 
	const wxString& name /* = "OpenCV Image" */)
	: wxScrolledWindow(parent, id, pos, size, style, name)
	, m_img_width(-1)
	, m_img_height(-1)
	, m_img_bpp(-1)
	, m_img_size(0) 
	, m_zoom_factor(1.0f)
	, m_draw_pos_x(0), m_draw_pos_y(0)
	, m_img_mode(k_img_rgb)
{
}

void c_ocv_canvas::on_init()
{
	
}
void c_ocv_canvas::on_paint(wxPaintEvent& event)
{
	wxBufferedPaintDC dc(this);
	PrepareDC(dc);

	if (is_current_valid())
	{ 
		if (k_img_rgb == m_img_mode && m_ocv_org_img->channels() > 1)
			draw_cv_img(dc, m_ocv_org_img); 
		else if (k_img_grayscale == m_img_mode)
			draw_cv_img(dc, m_ocv_gray); 
	}
	else  
	{
		//draw_blank(dc);
	}
} 


void c_ocv_canvas::on_erase_background(wxEraseEvent& event)
{
}

void c_ocv_canvas::on_size(wxSizeEvent& event)
{
	wxSize wnd_size = event.GetSize(); 
	int img_display_width = m_img_width * m_zoom_factor; 
	int img_display_height = m_img_height * m_zoom_factor; 
	m_draw_pos_x= (wxCoord)((wnd_size.x - img_display_width) * 0.5f); 
	m_draw_pos_y = (wxCoord)((wnd_size.y - img_display_height) * 0.5f);

	Refresh(true); 
}

bool c_ocv_canvas::is_current_valid() const
{
	return !m_ocv_org_img.empty(); 
}

int c_ocv_canvas::load_image(const wxString& img_file)
{
	// if there is already an image loaded, then unload first
	if (is_current_valid())
		unload_image();

	std::string file_name = wxstr_to_std(img_file);  
	cv::Mat temp = cv::imread(file_name.c_str(), CV_LOAD_IMAGE_COLOR);
	m_ocv_org_img = ocv_mat_ptr(new cv::Mat(temp));

	if (!m_ocv_org_img->data)
	{
		m_ocv_org_img->release();
		return -1;	
	}

	m_ocv_gray = ocv_mat_ptr(new cv::Mat(*m_ocv_org_img)); 
	// convert BGR to grayscale
	cvtColor(*m_ocv_org_img, *m_ocv_gray, CV_RGB2GRAY); 
	
	// Get image properties 
	m_img_width = m_ocv_org_img->cols;
	m_img_height = m_ocv_org_img->rows;
	m_img_bpp = m_ocv_org_img->elemSize();
	m_img_size = m_ocv_org_img->total() * m_ocv_org_img->elemSize(); 

	SetMinSize(wxSize(m_img_width, m_img_height)); 
	SetMaxSize(wxSize(m_img_width, m_img_height)); 
	SetSize(wxSize(m_img_width, m_img_height)); 

	Refresh(true); 

	return 0; 
}

void c_ocv_canvas::unload_image()
{
	if (!m_ocv_org_img.empty())
	{
		m_ocv_org_img.delete_obj(); 
		m_ocv_gray.delete_obj(); 
		assert(m_ocv_org_img.empty());
		assert(m_ocv_gray.empty());  
	}  
}

void c_ocv_canvas::draw_cv_img(wxDC& dc, ocv_mat_ptr& ocv_img) 
{
	if(ocv_img.empty())
		return; 
	
	cv::Mat temp = ocv_img->clone(); 
	if (ocv_img->channels() > 1)
	{
		cvtColor(*ocv_img, temp, CV_RGB2BGR); 
	} 
	else 
	{
		cvtColor(*ocv_img, temp, CV_GRAY2BGR); 
	}
	
	wxImage wx_img(temp.cols, temp.rows, temp.data, true); 
	wxBitmap wx_bitmap(wx_img);
	
	// Draw the bitmap
	dc.DrawBitmap(wx_bitmap, 0, 0); 
}

void c_ocv_canvas::draw_blank(wxDC& dc)
{
	wxBitmap wx_bitmap(512, 512);  
	dc.DrawBitmap(wx_bitmap, 0, 0);
} 