#include <sstream>
#include "wx/dc.h"
#include "wx/filedlg.h"
#include "wx/fileconf.h"
#include "overview_frame.h" 
#include "utils.h"
#include "ocv_canvas.h"
#include "ocv_cam_canvas.h"
#include "video_capture.h"

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
{
	get_videocap_mgr()->get_ocv_videocap(k_left_image)->open(0);
	
	m_cam_canvas_left->set_videocap_idx(k_left_image); 
	m_cam_canvas_left->active_render_loop(true); 
	m_cam_canvas_mid->set_videocap_idx(k_mid_image); 
	m_cam_canvas_right->set_videocap_idx(k_right_image);
}


//////////////////////////////////////////////////////////////////////////

c_overview_img_panel::c_overview_img_panel(wxWindow *parent, 
										wxWindowID id, 
										const wxPoint& pos, 
										const wxSize& size, 
										long style)
										: OverviewImgSubPanel(parent, id, pos, size, style)
{ 
	m_img_canvas_left->set_img_idx(k_left_image); 
	m_img_canvas_left->set_thumbnail_flag(true);

	m_img_canvas_mid->set_img_idx(k_mid_image);
	m_img_canvas_mid->set_thumbnail_flag(true);
	
	m_img_canvas_right->set_img_idx(k_right_image);
	m_img_canvas_right->set_thumbnail_flag(true); 
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
	switch(m_graph_type)
	{
	case k_graph_histogram:
		add_histograms(k_left_image); 
		add_histograms(k_mid_image); 
		add_histograms(k_right_image); 
		break;

	case k_graph_mtf:
		
		break;
	}
}

void c_overview_graph_panel::set_label_text(const wxString& label)
{
	wxStaticBoxSizer *static_box_sizer = static_cast<wxStaticBoxSizer*>(GetSizer());
	wxStaticBox *static_box = static_box_sizer->GetStaticBox(); 
	static_box->SetLabel(label); 
}

void c_overview_graph_panel::add_histograms(e_image_idx img_idx)
{	
	ocv_mat_ptr img = get_ocv_img_mgr()->get_grayscale_img(img_idx); 
	if (!is_ptr_null(img))
	{
		ocv_mat_ptr hist_mat = get_ocv_img_mgr()->calc_grayscale_hist(img_idx); 
		
		/// Prepare the histogram data
		hist_data_vec hist_data;
		hist_mat_to_vector(hist_mat, hist_data);
		
		switch (img_idx)
		{
		case k_left_image:
			setup_hist_graph(m_graph_wnd_left, hist_data);
			break;
		case k_mid_image:
			setup_hist_graph(m_graph_wnd_mid, hist_data); 
			break; 
		case k_right_image: 
			setup_hist_graph(m_graph_wnd_right, hist_data);
			break; 
		} 
	} 
}

void c_overview_graph_panel::add_mtf(e_image_idx img_idx)
{
	
	
}

void c_overview_graph_panel::setup_hist_graph(mpWindow *mp_wnd, hist_data_vec& hist_data)
{
	c_histogram_layar *hist_layer = new c_histogram_layar(hist_data);
	double min_x = hist_layer->GetMinX(); 
	double max_x = hist_layer->GetMaxX(); 
	double min_y = hist_layer->GetMinY(); 
	double max_y = hist_layer->GetMaxY(); 

	/// Setup the graph
	wxFont graph_font(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	mpScaleX *axis_x = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, true, mpX_NORMAL);
	mpScaleY *axis_y = new mpScaleY(wxT("Y"), mpALIGN_LEFT, true); 
	axis_x->SetFont(graph_font);
	axis_y->SetFont(graph_font);
	axis_x->SetDrawOutsideMargins(false); 
	axis_y->SetDrawOutsideMargins(false);

	mp_wnd->SetMargins(30, 10, 30, 60);
	mp_wnd->AddLayer(axis_x);
	mp_wnd->AddLayer(axis_y); 
	mp_wnd->AddLayer(hist_layer);

	mp_wnd->EnableDoubleBuffer(true);
	mp_wnd->Fit(min_x, max_x, min_y, max_y);
	mp_wnd->UpdateAll(); 
}

void c_overview_graph_panel::setup_mtf_graph(mpWindow *mp_wnd, mtf_data_vec& mtf_data)
{
	c_mtf_layer *mtf_layer = new c_mtf_layer(mtf_data);
	double min_x = mtf_layer->GetMinX(); 
	double max_x = mtf_layer->GetMaxX(); 
	double min_y = mtf_layer->GetMinY(); 
	double max_y = mtf_layer->GetMaxY(); 
	
	/// Setup the graph
	wxFont graph_font(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	mpScaleX *axis_x = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, true, mpX_NORMAL);
	mpScaleY *axis_y = new mpScaleY(wxT("Y"), mpALIGN_LEFT, true); 
	axis_x->SetFont(graph_font);
	axis_y->SetFont(graph_font);
	axis_x->SetDrawOutsideMargins(false); 
	axis_y->SetDrawOutsideMargins(false);

	mp_wnd->SetMargins(30, 10, 30, 60);
	mp_wnd->AddLayer(axis_x);
	mp_wnd->AddLayer(axis_y); 
	mp_wnd->AddLayer(mtf_layer); 

	mp_wnd->EnableDoubleBuffer(true);
	mp_wnd->Fit(min_x, max_x, min_y, max_y); 
	mp_wnd->UpdateAll(); 
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
	m_log_wnd->Show();  

	add_cam_sub_panel(wxT("Camera"));
	add_image_sub_panel(wxT("Images")); 
	add_graph_sub_panel(wxT("Histograms"), k_graph_histogram);

	restore_config();
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
}

void c_overview_frame::add_graph_sub_panel(const wxString& caption, e_graph_type graph_type)
{
	c_overview_graph_panel *graph_panel = new c_overview_graph_panel(this, graph_type, caption, wxID_OVERVIEW_GRAPH_PANEL);
	
	wxBoxSizer *box_sizer = static_cast<wxBoxSizer*>(GetSizer());
	wxSizerFlags sizer_flags(1); 
	sizer_flags.Expand().Border(20);
	box_sizer->Add(graph_panel, sizer_flags); 
	box_sizer->Layout(); 
}

void c_overview_frame::add_cam_sub_panel(const wxString& caption)
{
	c_overview_cam_panel *cam_panel = new c_overview_cam_panel(this, wxID_OVERVIEW_CAM_FRAME); 
	
	wxBoxSizer *box_sizer = static_cast<wxBoxSizer*>(GetSizer());
	wxSizerFlags sizer_flags(1); 
	sizer_flags.Expand().Border(20);
	box_sizer->Add(cam_panel, sizer_flags); 
	box_sizer->Layout();
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