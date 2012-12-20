#include <sstream>
#include "wx/dc.h"
#include "wx/filedlg.h"
#include "wx/fileconf.h"
#include "overview_frame.h" 
#include "utils.h"
#include "ocv_canvas.h"

static const wxString APP_NAME = wxT("LensCorrectionApp"); 
static const wxString FRAME_WIDTH_CONFIG_KEY = wxT("/ui_config/frame_width");
static const wxString FRAME_HEIGHT_CONFIG_KEY = wxT("/ui_config/frame_height"); 

c_overview_img_panel::c_overview_img_panel(wxWindow *parent, 
										wxWindowID id, 
										const wxPoint& pos, 
										const wxSize& size, 
										long style)
										: OverviewImgSubPanel(parent, id, pos, size, style)
										, m_img_loaded(false)
{ 

}

/*
void c_overview_img_panel::on_left_dbl_clk( wxMouseEvent& event )
{
	wxString wildcard_str; 
	wildcard_str += wxT("Image Files|*.jpg;*.tif|");
	wildcard_str += wxT("TIFF (*.tif)|*.tif|");
	wildcard_str += wxT("All Files (*.*)|*.*");

	wxString str; 
	str << wxT("Select image file to open!") << m_img_idx; 
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
*/

void c_overview_img_panel::draw_panel(wxDC& dc)
{
	
} 

/*
void c_overview_img_panel::open_image(const wxString& img_file)
{
	/// Load the image using the c_ocv_image_manager
	std::string file_name = wxstr_to_std(img_file);
	ocv_mat_ptr new_img = get_ocv_img_mgr()->load_from_file(file_name, m_img_idx);
	
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
		
		wxSize img_dimension = m_ocv_canvas->get_img_dimension();
		wxSize old_client_size = GetClientSize();
		wxSize offset = wxSize(std::max(img_dimension.GetWidth() - old_client_size.GetWidth(), 0), 
			std::max(img_dimension.GetHeight() - old_client_size.GetHeight(), 0));

		wxSize new_frame_size = wxSize(GetSize().GetWidth() + offset.GetWidth() + 10, GetSize().GetHeight() + offset.GetHeight() + 10);
		SetSize(new_frame_size); 
		SetMinSize(new_frame_size);
		SetMaxSize(new_frame_size);

		m_img_loaded = true; 
	}
}
*/ 


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

	add_image_sub_panel(wxT("Images")); 
	
	restore_config();
}

void c_overview_frame::on_close( wxCloseEvent& event )
{ 
	wxSize frame_size = GetSize(); 
	
	// Write the size of windows to config
	wxFileConfig::Get()->Write(FRAME_WIDTH_CONFIG_KEY, frame_size.GetWidth()); 
	wxFileConfig::Get()->Write(FRAME_HEIGHT_CONFIG_KEY, frame_size.GetHeight()); 

	OverviewFrame::OnCloseWindow(event);
}

void c_overview_frame::on_size( wxSizeEvent& event )
{
	event.Skip(); 
}

void c_overview_frame::add_image_sub_panel(const wxString& caption)
{	
	c_overview_img_panel *img_panel = new c_overview_img_panel(this); 

	wxBoxSizer *box_sizer = static_cast<wxBoxSizer*>(GetSizer());
	wxSizerFlags sizer_flags(0); 
	sizer_flags.Expand().Border(10);
	box_sizer->Add(img_panel, sizer_flags); 
	box_sizer->Layout(); 
}

void c_overview_frame::add_graph_sub_panel(const wxString& caption)
{
	
}

void c_overview_frame::init_config()
{ 
	// Create a global file config object 
	wxFileConfig *file_config = new wxFileConfig(APP_NAME); 
	wxFileConfig::Set(file_config);  
}

void c_overview_frame::restore_config()
{
	// Read the config file
	double frame_width = 0;
	double frame_height = 0; 
	wxFileConfig::Get()->SetPath(wxT("/ui_config"));
	wxFileConfig::Get()->Read(wxT("frame_width"), &frame_width); 
	wxFileConfig::Get()->Read(wxT("frame_height"), &frame_height); 

	SetSize(frame_width, frame_height); 
}