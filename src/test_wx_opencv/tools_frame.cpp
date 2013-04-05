#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "wx/wx.h"
#include "tools_frame.h"
#include "overview_frame.h"
#include "image.h"
#include "utils.h"
#include "graph_canvas.h"

const std::string img_ext = ".png";

c_tools_frame::c_tools_frame(wxWindow* parent,
							c_overview_frame *overview_frame, 
							wxWindowID id, 
							const wxString& title, 
							const wxPoint& pos, 
							const wxSize& size, 
							long style)
							: super(parent, id, title, pos, size, style)
							, m_overview_frame(overview_frame)
{	
}

bool c_tools_frame::validate_input()
{
	bool is_valid_angle = true; 
	wxString rotation_angle = m_text_rotation->GetLineText(0); 
	std::string std_rotation_angle = wxstr_to_std(rotation_angle); 
	std::string::const_iterator it = std_rotation_angle.begin();
	for (; it != std_rotation_angle.end(); ++it)
	{
		if (!isdigit(*it))
			is_valid_angle = false; 
	}

	if (!is_valid_angle) 
		return false;


	return true; 
}

void c_tools_frame::on_save_report( wxCommandEvent& event )
{
	if (!validate_input())
	{
		wxMessageBox(_T("Please input valid parameters! "));
		return;
	}

	// Close all the cameras first 
	m_overview_frame->get_overview_cam_panel()->close_all_cams(); 
	wxDirDialog dlg(NULL, _T("Choose input directory"), _T(""), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST); 

	if (dlg.ShowModal() == wxID_OK) 
	{
		wxString dir_path = dlg.GetPath();
		wxString folder_name = make_folder_name(); 
		wxString path = dir_path + wxT("\\") + folder_name;
		if (!wxFileName::DirExists(path))
			wxFileName::Mkdir(path, 0777, wxPATH_MKDIR_FULL);

		write_grayscale_imgs(path); 
		write_hist_graphs(path); 
		write_mtf_graphs(path); 
	}
} 

wxString c_tools_frame::make_folder_name()
{
	/* 
	wxString date_time_str = wxDateTime::Now().Format(_T("%y_%m_%d_%H_%M_%S")); 
	wxString lens_name = m_txt_lens_name->GetLineText(0);

	return date_time_str + lens_name;
	*/ 
	
	wxString project_name = m_text_project->GetLineText(0); 
	if (project_name.IsEmpty()) 
	{
		wxString date_time_str = wxDateTime::Now().Format(_T("%y_%m_%d_%H_%M_%S")); 
		return date_time_str; 
	}
	else 
		return project_name; 
}

int c_tools_frame::write_grayscale_imgs(const wxString& path)
{
	{
		std::string name = m_overview_frame->m_current_left_grayscale_img_name; 
		ocv_mat_ptr img = get_ocv_img_mgr()->find_image_by_name(name); 
		
		if (is_image_valid(img))
		{
			std::string std_path = wxstr_to_std(path) + "\\" + name + img_ext;
			std::vector<int> compression_params;
			compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
			compression_params.push_back(9);
			//cv::imshow("hehe", *img); 
			cv::imwrite(std_path, *img, compression_params); 
		}
	}

	{
		std::string name = m_overview_frame->m_current_mid_grayscale_img_name; 
		ocv_mat_ptr img = get_ocv_img_mgr()->find_image_by_name(name); 

		if (is_image_valid(img))
		{
			std::string std_path = wxstr_to_std(path) + "\\" + name + img_ext;
			std::vector<int> compression_params;
			compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
			compression_params.push_back(9);
			cv::imwrite(std_path, *img, compression_params); 
		}
	}

	
	{
		std::string name = m_overview_frame->m_current_right_grayscale_img_name; 
		ocv_mat_ptr img = get_ocv_img_mgr()->find_image_by_name(name); 

		if (is_image_valid(img))
		{
			std::string std_path = wxstr_to_std(path) + "\\" + name + img_ext;
			std::vector<int> compression_params;
			compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
			compression_params.push_back(9);
			cv::imwrite(std_path, *img, compression_params); 
		}
	}

	return 0; 
}

int c_tools_frame::write_hist_graphs(const wxString& path)
{
	c_graph_canvas *left = m_overview_frame->get_overview_graph_panel_hist()->get_left_graph_canvas(); 
	c_graph_canvas *mid = m_overview_frame->get_overview_graph_panel_hist()->get_mid_graph_canvas(); 
	c_graph_canvas *right = m_overview_frame->get_overview_graph_panel_hist()->get_right_graph_canvas();

	std::string name = m_overview_frame->m_current_left_grayscale_img_name + "-hist"; 
	
	wxString full_path = path + _T("\\") + stdstr_to_wx(name) + _T(".bmp"); 
	left->SaveScreenshot(full_path);

	//////////////////////////////////////////////////////////////////////////
	name = m_overview_frame->m_current_mid_grayscale_img_name + "-hist"; 

	full_path = path + _T("\\") + stdstr_to_wx(name) + _T(".bmp"); 
	mid->SaveScreenshot(full_path);

	//////////////////////////////////////////////////////////////////////////
	name = m_overview_frame->m_current_right_grayscale_img_name + "-hist"; 

	full_path = path + _T("\\") + stdstr_to_wx(name) + _T(".bmp"); 
	right->SaveScreenshot(full_path);
	return 0; 
}

int c_tools_frame::write_mtf_graphs(const wxString& path)
{
	c_graph_canvas *left = m_overview_frame->get_overview_graph_panel_mtf()->get_left_graph_canvas(); 
	c_graph_canvas *mid = m_overview_frame->get_overview_graph_panel_mtf()->get_mid_graph_canvas(); 
	c_graph_canvas *right = m_overview_frame->get_overview_graph_panel_mtf()->get_right_graph_canvas();

	std::string name = m_overview_frame->m_current_left_grayscale_img_name + "-mtf"; 

	wxString full_path = path + _T("\\") + stdstr_to_wx(name) + _T(".bmp"); 
	left->SaveScreenshot(full_path);

	//////////////////////////////////////////////////////////////////////////
	name = m_overview_frame->m_current_mid_grayscale_img_name + "-mtf"; 

	full_path = path + _T("\\") + stdstr_to_wx(name) + _T(".bmp"); 
	mid->SaveScreenshot(full_path);

	//////////////////////////////////////////////////////////////////////////
	name = m_overview_frame->m_current_right_grayscale_img_name + "-mtf"; 

	full_path = path + _T("\\") + stdstr_to_wx(name) + _T(".bmp"); 
	right->SaveScreenshot(full_path);
	return 0; 
}
