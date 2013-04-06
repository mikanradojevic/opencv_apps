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
	m_cam_canvas->Update();
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
								, m_camera_opened(false)
{ 
	m_render_timer = new c_render_timer(this); 
	m_current_frame = make_ocv_image(1, 1); 
	get_ocv_img_mgr()->add_image("cam_image", m_current_frame);
	// m_current_frame = get_ocv_img_mgr()->add_grayscale_img("cam_img", 0, 0);
} 

c_ocv_cam_canvas::~c_ocv_cam_canvas()
{
	if (m_render_timer) 
		delete m_render_timer; 
	m_render_timer = NULL;
}

void c_ocv_cam_canvas::on_paint(wxPaintEvent& event)
{	
	if (!m_render_loop_on)
	{
		event.Skip(); 
		return; 
	}
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

	// cv::Mat frame; 
	cv::Mat resized;
	videocap_mgr->get_ocv_videocap(m_videocap_idx)->retrieve(*m_current_frame); 

	wxSize client_size = GetClientSize();
	cv::Size cv_size(client_size.GetWidth(), client_size.GetHeight());
	cv::resize(*m_current_frame, resized, cv_size, 0.0, 0.0, cv::INTER_LINEAR);
	
	cv::Mat temp = resized.clone();
	//cvtColor(*resized_img, temp, CV_GRAY2BGR); 
	cvtColor(resized, temp, CV_RGB2BGR); 
	wxImage wx_img(temp.cols, temp.rows, temp.data, true); 
	wxBitmap wx_bitmap(wx_img);
	
	// Draw the bitmap 
	dc.DrawBitmap(wx_bitmap, 0, 0); 

	if (!m_camera_opened) 
		m_camera_opened = true;
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
	m_camera_opened = on;
	m_render_loop_on = on; 
	m_render_timer->Stop(); 

	if (on)
		m_render_timer->Start(10000, true); 
	else
		m_render_timer->Stop();  
	
	Refresh(); 
	Update(); 
}

ocv_mat_ptr c_ocv_cam_canvas::get_current_frame() 
{
	return m_current_frame; 
}