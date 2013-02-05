#include "ocv_cam_canvas.h" 
#include "video_capture.h"
#include "image.h"

BEGIN_EVENT_TABLE(c_ocv_cam_canvas, wxScrolledWindow) 
	EVT_PAINT(c_ocv_cam_canvas::on_paint) 
	EVT_IDLE(c_ocv_cam_canvas::on_idle)
	// EVT_SIZE(c_ocv_cam_canvas::on_size)
END_EVENT_TABLE() 

//////////////////////////////////////////////////////////////////////////

class c_render_timer : public wxTimer
{
public:
	c_render_timer(c_ocv_cam_canvas *cam_canvas); 
	void Notify();
	void start();

private:
	c_ocv_cam_canvas *m_cam_canvas; 
}; 

c_render_timer::c_render_timer(c_ocv_cam_canvas *cam_canvas)
	: wxTimer()
	, m_cam_canvas(cam_canvas)
{}

void c_render_timer::Notify()
{
	m_cam_canvas->Refresh(); 
}

void c_render_timer::start()
{
	wxTimer::Start(1000);
}

////////////////////////////////////////////////////////////////////////// 

c_ocv_cam_canvas::c_ocv_cam_canvas(wxWindow *parent, 
								wxWindowID id, 
								const wxPoint& pos, 
								const wxSize& size, 
								long style, 
								const wxString& name)
								: super(parent, id, pos, size, style, name)
								, m_render_loop_on(false)
{ 
	m_render_timer = new c_render_timer(this); 
}

c_ocv_cam_canvas::~c_ocv_cam_canvas()
{
	if (m_render_timer) 
		delete m_render_timer; 
	m_render_timer = NULL;
}

void c_ocv_cam_canvas::on_paint(wxPaintEvent& event)
{
	wxClientDC dc(this);
	draw_captured(dc); 
}

void c_ocv_cam_canvas::draw_captured(wxDC& dc)
{
	// Grab the next frame from camera
	c_videocap_manager *videocap_mgr = get_videocap_mgr(); 
	bool is_open = videocap_mgr->get_ocv_videocap(m_videocap_idx)->isOpened(); 

	if (!videocap_mgr || !is_open)
		return; 

	videocap_mgr->get_ocv_videocap(m_videocap_idx)->grab();
	
	/*
	ocv_mat_ptr image = get_ocv_img_mgr()->get_grayscale_img(m_videocap_idx);
	if (image == ocv_mat_ptr()) 
	{
		// Create a new greyscale image
		wxSize client_size = GetClientSize();
		get_ocv_img_mgr()->new_greyscale_img(m_videocap_idx, client_size.GetWidth(), client_size.GetHeight());
		image = get_ocv_img_mgr()->get_grayscale_img(m_videocap_idx);
	}
	*/
	cv::Mat frame; 
	cv::Mat resized;
	videocap_mgr->get_ocv_videocap(m_videocap_idx)->retrieve(frame); 

	wxSize client_size = GetClientSize();
	cv::Size cv_size(client_size.GetWidth(), client_size.GetHeight());
	cv::resize(frame, resized, cv_size, 0.0, 0.0, cv::INTER_LINEAR);
	
	cv::Mat temp = resized.clone();
	//cvtColor(*resized_img, temp, CV_GRAY2BGR); 
	cvtColor(resized, temp, CV_RGB2BGR); 
	wxImage wx_img(temp.cols, temp.rows, temp.data, true); 
	wxBitmap wx_bitmap(wx_img);
	
	// Draw the bitmap
	dc.DrawBitmap(wx_bitmap, 0, 0); 
}

void c_ocv_cam_canvas::on_idle(wxIdleEvent& event)
{
	if (m_render_loop_on)
	{
		draw_now(); 
		event.RequestMore();
	}
}

void c_ocv_cam_canvas::draw_now()
{
	wxClientDC dc(this);
	// PrepareDC(dc);
	draw_captured(dc); 
}

void c_ocv_cam_canvas::active_render_loop(bool on)
{
	if (on && !m_render_loop_on) 
	{
		m_render_loop_on = true;
	}
	else if (!on && m_render_loop_on) 
	{
		m_render_loop_on = false; 
	}
}

