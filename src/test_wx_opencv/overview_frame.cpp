#include <sstream>
#include "wx/dc.h"
#include "wx/filedlg.h"
#include "wx/fileconf.h"
#include "overview_frame.h" 
#include "utils.h"
#include "ocv_canvas.h"
#include "ocv_cam_canvas.h"
#include "video_capture.h"
#include "graph_canvas.h"
#include "image_frame.h"

static const wxString APP_NAME = wxT("LensCorrectionApp"); 
static const wxString UI_CONFIG_PATH = wxT("/ui_config");
static const wxString FRAME_WIDTH_CONFIG_KEY = UI_CONFIG_PATH + wxT("/frame_width");
static const wxString FRAME_HEIGHT_CONFIG_KEY = UI_CONFIG_PATH + wxT("/frame_height"); 
static const wxString FRAME_POS_X_CONFIG_KEY = UI_CONFIG_PATH + wxT("/frame_posx");
static const wxString FRAME_POS_Y_CONFIG_KEY = UI_CONFIG_PATH + wxT("/frame_posy");

c_overview_cam_panel::c_overview_cam_panel(wxWindow *parent, 
										wxWindowID id /* = wxID_ANY */, 
										const wxPoint& pos /* = wxDefaultPosition */, 
										const wxSize& size /* = wxDefaultSize */, 
										long style /* = wxTAB_TRAVERSAL */)
										: OverviewVideoSubPanel(parent, id, pos, size, style)
										, m_rotation_angle(0)
{ 
	m_overview_frame = static_cast<c_overview_frame*>(parent);

	m_cam_canvas_left->set_videocap_idx(k_left_image); 
	m_cam_canvas_mid->set_videocap_idx(k_mid_image); 
	m_cam_canvas_right->set_videocap_idx(k_right_image); 
}

void c_overview_cam_panel::on_capture_left_click( wxCommandEvent& event )
{	
	ocv_mat_ptr img = m_cam_canvas_left->get_current_frame();
	if (m_cam_canvas_left->is_camera_opened() && is_image_valid(img))
	{
		if (m_overview_frame)
		{
			get_ocv_img_mgr()->add_image(LEFT_IMAGE_ORIGINAL_NAME, img); 
			
			wx_log_message("111111");

			// Convert RGB to Grayscale
			cv::Mat temp = img->clone();
			ocv_mat_ptr grayscale_img = ocv_mat_ptr(new cv::Mat(temp));
			cvtColor(*img, *grayscale_img,  CV_RGB2GRAY); 

			wx_log_message("22222");

			std::stringstream ss; 
			ss << m_rotation_angle; 
			m_overview_frame->m_current_left_grayscale_img_name = LEFT_IMAGE_GRAYSCALE_NAME + "-" + ss.str(); 
			get_ocv_img_mgr()->add_left_grayscale_image(grayscale_img, m_rotation_angle);

			wx_log_message("33333");

			// Show the image on the image panel 
			c_overview_img_panel *img_panel = m_overview_frame->get_overview_img_panel(); 
			std::string name = "left_image"; 
			img_panel->get_ocv_canvas(k_left_image)->set_image(img, name); 

			wx_log_message("444444");

			// Calculate the histogram
			c_overview_graph_panel *hist_panel = m_overview_frame->get_overview_graph_panel_hist();
			hist_panel->calculate_histogram(grayscale_img, k_left_image); 
			hist_panel->UpdateWindowUI(wxUPDATE_UI_RECURSE);

			wx_log_message("55555");
		}
	}	
}

void c_overview_cam_panel::on_capture_mid_click( wxCommandEvent& event ) 
{ 
	ocv_mat_ptr img = m_cam_canvas_mid->get_current_frame();
	if (m_cam_canvas_mid->is_camera_opened() && is_image_valid(img))
	{
		if (m_overview_frame)
		{
			get_ocv_img_mgr()->add_image(MID_IMAGE_ORIGINAL_NAME, img); 

			wx_log_message("111111");

			// Convert RGB to Grayscale
			cv::Mat temp = img->clone();
			ocv_mat_ptr grayscale_img = ocv_mat_ptr(new cv::Mat(temp));
			cvtColor(*img, *grayscale_img,  CV_RGB2GRAY); 

			wx_log_message("22222");

			std::stringstream ss; 
			ss << m_rotation_angle; 
			m_overview_frame->m_current_mid_grayscale_img_name = MID_IMAGE_GRAYSCALE_NAME + "-" + ss.str(); 
			get_ocv_img_mgr()->add_mid_grayscale_image(grayscale_img, m_rotation_angle);

			wx_log_message("33333");

			// Show the image on the image panel 
			c_overview_img_panel *img_panel = m_overview_frame->get_overview_img_panel(); 
			std::string name = "mid_image"; 
			img_panel->get_ocv_canvas(k_mid_image)->set_image(img, name); 

			wx_log_message("444444");

			// Calculate the histogram
			c_overview_graph_panel *hist_panel = m_overview_frame->get_overview_graph_panel_hist();
			hist_panel->calculate_histogram(grayscale_img, k_mid_image); 
			hist_panel->UpdateWindowUI(wxUPDATE_UI_RECURSE);
			
		}
	}
}

void c_overview_cam_panel::on_capture_right_click( wxCommandEvent& event )
{ 
	
	ocv_mat_ptr img = m_cam_canvas_right->get_current_frame();
	e_image_idx img_idx = k_right_image; 
	if (m_cam_canvas_right->is_camera_opened() && is_image_valid(img))
	{
		if (m_overview_frame)
		{
			get_ocv_img_mgr()->add_image(RIGHT_IMAGE_ORIGINAL_NAME, img); 

			// Convert RGB to Grayscale
			cv::Mat temp = img->clone();
			ocv_mat_ptr grayscale_img = ocv_mat_ptr(new cv::Mat(temp));
			cvtColor(*img, *grayscale_img,  CV_RGB2GRAY); 
			temp.release();

			std::stringstream ss; 
			ss << m_rotation_angle; 
			m_overview_frame->m_current_right_grayscale_img_name = RIGHT_IMAGE_GRAYSCALE_NAME + "-" + ss.str(); 
			get_ocv_img_mgr()->add_right_grayscale_image(grayscale_img, m_rotation_angle);

			// Show the image on the image panel 
			c_overview_img_panel *img_panel = m_overview_frame->get_overview_img_panel(); 
			std::string name = "right_image"; 
			img_panel->get_ocv_canvas(k_right_image)->set_image(img, name); 

			// Calculate the histogram
			c_overview_graph_panel *hist_panel = m_overview_frame->get_overview_graph_panel_hist();
			hist_panel->calculate_histogram(grayscale_img, k_right_image); 
			hist_panel->UpdateWindowUI(wxUPDATE_UI_RECURSE);
		}
	}
}

void c_overview_cam_panel::on_open_cam_left_click( wxCommandEvent& event )
{
	
	close_all_cams();
	get_videocap_mgr()->get_ocv_videocap(k_left_image)->open(0); 
	m_cam_canvas_left->set_videocap_idx(k_left_image); 
	m_cam_canvas_left->active_render_loop(true); 
	
}

void c_overview_cam_panel::on_open_cam_mid_click( wxCommandEvent& event )
{
	close_all_cams(); 
	get_videocap_mgr()->get_ocv_videocap(k_mid_image)->open(1); 
	m_cam_canvas_mid->set_videocap_idx(k_mid_image); 
	m_cam_canvas_mid->active_render_loop(true);
}

void c_overview_cam_panel::on_open_cam_right_click( wxCommandEvent& event )
{
	
	close_all_cams(); 
	get_videocap_mgr()->get_ocv_videocap(k_right_image)->open(2); 
	m_cam_canvas_right->set_videocap_idx(k_right_image); 
	m_cam_canvas_right->active_render_loop(true); 
}

void c_overview_cam_panel::close_all_cams()
{
	
	if (get_videocap_mgr()->get_ocv_videocap(k_left_image)->isOpened())
	{
		get_videocap_mgr()->get_ocv_videocap(k_left_image)->release(); 
		m_cam_canvas_left->active_render_loop(false); 
	}
	 
	if (get_videocap_mgr()->get_ocv_videocap(k_mid_image)->isOpened())
	{
		get_videocap_mgr()->get_ocv_videocap(k_mid_image)->release(); 
		m_cam_canvas_mid->active_render_loop(false); 
	}
	
	if (get_videocap_mgr()->get_ocv_videocap(k_right_image)->isOpened())
	{
		get_videocap_mgr()->get_ocv_videocap(k_right_image)->release();
		m_cam_canvas_right->active_render_loop(false); 
	}
	 
}

//////////////////////////////////////////////////////////////////////////

c_overview_img_panel::c_overview_img_panel(wxWindow *parent, 
										wxWindowID id, 
										const wxPoint& pos, 
										const wxSize& size, 
										long style)
										: OverviewImgSubPanel(parent, id, pos, size, style)
{ 
	m_overview_frame = static_cast<c_overview_frame*>(parent); 
	assert(m_overview_frame);  
} 


c_ocv_canvas* c_overview_img_panel::get_ocv_canvas(e_image_idx img_idx) 
{
	c_ocv_canvas *ret = NULL;
	switch (img_idx)
	{
	case k_left_image:
		ret = m_img_canvas_left;
		break;
	case k_mid_image:
		ret = m_img_canvas_mid;
		break; 
	case k_right_image: 
		ret = m_img_canvas_right;
		break; 
	} 
	assert(ret != NULL);
	return ret;
}

void c_overview_img_panel::on_left_img_thunmnail_double_click(wxMouseEvent& event)
{
	ocv_mat_ptr left_grayscale_img = get_ocv_img_mgr()->find_image_by_name(m_overview_frame->m_current_left_grayscale_img_name); 
	if (left_grayscale_img)
	{ 
		c_image_frame *img_frame = new c_image_frame(m_overview_frame, wxID_IMAGE_FRAME);
		img_frame->set_image(left_grayscale_img, LEFT_IMAGE_GRAYSCALE_NAME, k_left_image);
		img_frame->Show(); 
	}
}

void c_overview_img_panel::on_mid_img_thunmnail_double_click( wxMouseEvent& event )
{
	ocv_mat_ptr grayscale_img = get_ocv_img_mgr()->find_image_by_name(m_overview_frame->m_current_mid_grayscale_img_name); 
	if (grayscale_img)
	{ 
		c_image_frame *img_frame = new c_image_frame(m_overview_frame, wxID_IMAGE_FRAME);
		img_frame->set_image(grayscale_img, MID_IMAGE_GRAYSCALE_NAME, k_mid_image);
		img_frame->Show(); 
	}
}

void c_overview_img_panel::on_right_img_thunmnail_double_click( wxMouseEvent& event )
{ 
	ocv_mat_ptr grayscale_img = get_ocv_img_mgr()->find_image_by_name(m_overview_frame->m_current_right_grayscale_img_name); 
	if (grayscale_img)
	{ 
		c_image_frame *img_frame = new c_image_frame(m_overview_frame, wxID_IMAGE_FRAME);
		img_frame->set_image(grayscale_img, RIGHT_IMAGE_GRAYSCALE_NAME, k_right_image);
		img_frame->Show(); 
	}
}


//////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(c_overview_graph_panel, OverviewGraphSubPanel)
	EVT_CUSTOM(wxEVT_IMG_LOADED_CMD, wxID_ANY, c_overview_graph_panel::on_img_loaded)	
END_EVENT_TABLE()

c_overview_graph_panel::c_overview_graph_panel(wxWindow *parent, 
											e_graph_type graph_type,
											const wxString& title,  
											wxWindowID id, 
											const wxPoint& pos, 
											const wxSize& size, 
											long style)
											: OverviewGraphSubPanel(parent, id, pos, size, style)
											, m_graph_type(graph_type)
{
	set_label_text(title);
	update_graph();
}

void c_overview_graph_panel::update_graph()
{
	/*
	switch(m_graph_type)
	{
	case k_graph_histogram:
		add_histogram(k_left_image); 
		add_histogram(k_mid_image); 
		add_histogram(k_right_image); 
		break;

	case k_graph_mtf:
		
		break;
	} 
	*/
}

void c_overview_graph_panel::set_label_text(const wxString& label)
{
	wxStaticBoxSizer *static_box_sizer = static_cast<wxStaticBoxSizer*>(GetSizer());
	wxStaticBox *static_box = static_box_sizer->GetStaticBox(); 
	static_box->SetLabel(label); 
}

void c_overview_graph_panel::calculate_histogram(ocv_mat_ptr img, e_image_idx img_idx)
{
	if (!is_ptr_null(img))
	{
		/// Prepare the histogram data
		hist_data_vec hist_data;
		ocv_mat_ptr hist_mat = calc_hist(img);
		hist_mat_to_vector(hist_mat, hist_data);
		
		switch (img_idx)
		{
		case k_left_image:
			m_graph_wnd_left->setup_hist_graph(hist_data);
			m_graph_wnd_left->Refresh();
			m_graph_wnd_left->Update(); 
			break;
		case k_mid_image:
			m_graph_wnd_mid->setup_hist_graph(hist_data);
			m_graph_wnd_mid->Refresh();
			m_graph_wnd_mid->Update(); 
			break; 
		case k_right_image: 
			m_graph_wnd_right->setup_hist_graph(hist_data);
			m_graph_wnd_right->Refresh();
			m_graph_wnd_right->Update(); 
			break; 
		} 
	} 
} 

void c_overview_graph_panel::calculate_mtf(ocv_mat_ptr img, e_image_idx img_idx, wxPoint& start, wxPoint& end)
{
	if (!is_ptr_null(img))
	{
		mtf_data_vec mtf_data;
		cv::Point p1(start.x, start.y);
		cv::Point p2(end.x, end.y); 
		if (p1.x == p2.x && p1.y == p2.y)
			return; 
		
		calc_mtf(img, p1, p2, mtf_data);

		switch (img_idx)
		{
		case k_left_image:
			m_graph_wnd_left->setup_mtf_graph(mtf_data);
			break;
		case k_mid_image:
			m_graph_wnd_mid->setup_mtf_graph(mtf_data);
			break; 
		case k_right_image: 
			m_graph_wnd_right->setup_mtf_graph(mtf_data);
			break; 
		}  
	}
} 

void c_overview_graph_panel::on_img_loaded(wxEvent& event)
{
	wxLogDebug(wxT("Image has been loaded!")); 
	update_graph();

	Refresh(true);
}

//////////////////////////////////////////////////////////////////////////


c_overview_frame::c_overview_frame(wxWindow *parent, 
							wxWindowID id, 
							const wxString& title, 
							const wxPoint& pos, 
							const wxSize& size,
							long style)
							: OverviewFrame(parent, id, title, pos, size, style) 
{ 
	/// Init config system 
	init_config(); 

	/// Create logging window 
	wxLogChain *log_chain = new wxLogChain(new wxLogGui());
	m_log_wnd = new wxLogWindow(this, wxT("Log"), false, true); 
	wxWindow *log_text_ctrl = m_log_wnd->GetFrame()->GetChildren().GetFirst()->GetData(); 
	log_text_ctrl->SetFont(wxFont(9, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	m_log_wnd->GetFrame()->SetSize(650, 800); 
	// m_log_wnd->Show();  

	add_cam_sub_panel(wxT("Camera"));
	add_image_sub_panel(wxT("Images")); 
	add_graph_sub_panel(wxT("Histograms"), k_graph_histogram); 
	add_graph_sub_panel(wxT("MTF"), k_graph_mtf); 

	restore_config();

	Refresh();
	Update();
}

c_overview_frame::~c_overview_frame() 
{
	write_config(); 
}

void c_overview_frame::add_image_sub_panel(const wxString& caption)
{	
	c_overview_img_panel *img_panel = new c_overview_img_panel(this, wxID_OVERVIEW_IMG_PANEL); 

	wxBoxSizer *box_sizer = static_cast<wxBoxSizer*>(GetSizer());
	wxSizerFlags sizer_flags(1); 
	sizer_flags.Expand().Border(20);
	box_sizer->Add(img_panel, sizer_flags); 
	box_sizer->Layout(); 

	img_panel->Refresh(); 
	img_panel->Update(); 
}

void c_overview_frame::add_graph_sub_panel(const wxString& caption, e_graph_type graph_type)
{
	c_overview_graph_panel *graph_panel = NULL; 
	switch (graph_type) 
	{
	case k_graph_histogram:
		graph_panel = new c_overview_graph_panel(this, graph_type, caption, wxID_OVERVIEW_GRAPH_PANEL_HIST); 
		break; 
	case k_graph_mtf: 
		graph_panel = new c_overview_graph_panel(this, graph_type, caption, wxID_OVERVIEW_GRAPH_PANEL_MTF);
		break;
	} 
	
	wxBoxSizer *box_sizer = static_cast<wxBoxSizer*>(GetSizer());
	wxSizerFlags sizer_flags(1); 
	sizer_flags.Expand().Border(20);
	box_sizer->Add(graph_panel, sizer_flags); 
	box_sizer->Layout(); 

	graph_panel->Refresh();
	graph_panel->Update();
}

void c_overview_frame::add_cam_sub_panel(const wxString& caption)
{
	c_overview_cam_panel *cam_panel = new c_overview_cam_panel(this, wxID_OVERVIEW_CAM_FRAME); 
	
	wxBoxSizer *box_sizer = static_cast<wxBoxSizer*>(GetSizer());
	wxSizerFlags sizer_flags(1); 
	sizer_flags.Expand().Border(20);
	box_sizer->Add(cam_panel, sizer_flags); 
	box_sizer->Layout();

	cam_panel->Refresh();
	cam_panel->UpdateWindowUI(wxUPDATE_UI_RECURSE); 
}

void c_overview_frame::init_config()
{ 
	// Create a global file config object 
	wxFileConfig *file_config = new wxFileConfig(APP_NAME); 
	wxFileConfig::Set(file_config);  
}

void c_overview_frame::restore_config()
{
	// Read the size of the main frame
	double frame_width = 0;
	double frame_height = 0; 
	wxFileConfig::Get()->Read(FRAME_WIDTH_CONFIG_KEY, &frame_width); 
	wxFileConfig::Get()->Read(FRAME_HEIGHT_CONFIG_KEY, &frame_height); 
	SetSize(frame_width, frame_height); 

	// Read the position of the main frame on screen 
	double frame_posx = 0;
	double frame_posy = 0;
	wxFileConfig::Get()->Read(FRAME_POS_X_CONFIG_KEY, &frame_posx);
	wxFileConfig::Get()->Read(FRAME_POS_Y_CONFIG_KEY, &frame_posy);
	SetPosition(wxPoint(frame_posx, frame_posy)); 
}

void c_overview_frame::write_config()
{
	// Write the size of windows to config
	wxSize frame_size = GetSize(); 
	wxFileConfig::Get()->Write(FRAME_WIDTH_CONFIG_KEY, frame_size.GetWidth()); 
	wxFileConfig::Get()->Write(FRAME_HEIGHT_CONFIG_KEY, frame_size.GetHeight()); 

	// Write the position of main frame
	wxPoint frame_pos = GetPosition();
	wxFileConfig::Get()->Write(FRAME_POS_X_CONFIG_KEY, frame_pos.x);
	wxFileConfig::Get()->Write(FRAME_POS_Y_CONFIG_KEY, frame_pos.y);
}

c_overview_cam_panel* c_overview_frame::get_overview_cam_panel()
{
	c_overview_cam_panel *cam_panel = static_cast<c_overview_cam_panel*>(this->FindWindowById(wxID_OVERVIEW_CAM_FRAME));
	return cam_panel; 
}

c_overview_img_panel* c_overview_frame::get_overview_img_panel()
{
	c_overview_img_panel *img_panel = static_cast<c_overview_img_panel*>(this->FindWindowById(wxID_OVERVIEW_IMG_PANEL)); 
	return img_panel; 
}

c_overview_graph_panel* c_overview_frame::get_overview_graph_panel_hist()
{
	c_overview_graph_panel *graph_panel = static_cast<c_overview_graph_panel*>(this->FindWindowById(wxID_OVERVIEW_GRAPH_PANEL_HIST));
	return graph_panel; 
}

c_overview_graph_panel* c_overview_frame::get_overview_graph_panel_mtf()
{
	c_overview_graph_panel *graph_panel = static_cast<c_overview_graph_panel*>(this->FindWindowById(wxID_OVERVIEW_GRAPH_PANEL_MTF));
	return graph_panel; 
}


void c_overview_frame::on_save_report( wxCommandEvent& event )
{
	wxDirDialog* save_report_dlg =
		new wxDirDialog( this, _("Save Report"), _(""),  
		wxDD_DEFAULT_STYLE, wxDefaultPosition);

	if ( save_report_dlg->ShowModal() == wxID_OK )
	{
		/*
		SetCurrentFilename(save_report_dlg->GetFilename());
		theText->LoadFile(save_report_dlg->GetFilename());
		SetStatusText(GetCurrentFilename(), 0);
		SetStatusText(save_report_dlg->GetDirectory(),1);
		*/

		//wxString 
		
	
		//::wxMkdir 
	}
}

wxString c_overview_frame::generate_dir_name()
{
	
	return wxT(""); 
	
}