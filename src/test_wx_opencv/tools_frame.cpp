#include <stdio.h>
#include "wx/wx.h"
#include "tools_frame.h"
#include "overview_frame.h"
#include "image.h"
#include "utils.h"

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


void c_tools_frame::on_save_report( wxCommandEvent& event )
{
	// Close all the cameras first 
	m_overview_frame->get_overview_cam_panel()->close_all_cams(); 

	wxDirDialog dlg(NULL, _T("Choose input directory"), _T(""), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST); 

	if (dlg.ShowModal() == wxID_OK) 
	{
		wxString dir_path = dlg.GetPath();
		wxString folder_name = make_folder_name(); 
		wxString path = dir_path + wxT("\\") + folder_name; 
		wxFileName::Mkdir(path, 0777, wxPATH_MKDIR_FULL);

		write_grayscale_imgs(path); 
	}
} 

wxString c_tools_frame::make_folder_name()
{
	wxString date_time_str = wxDateTime::Now().Format(_T("%y_%m_%d_%H_%M_%S")); 
	wxString lens_name = m_txt_lens_name->GetLineText(0);

	return date_time_str + lens_name; 
}

int c_tools_frame::write_grayscale_imgs(const wxString& path)
{
	std::vector<std::string> left_names = get_ocv_img_mgr()->get_left_grayscale_img_names();
	std::vector<std::string> mid_names = get_ocv_img_mgr()->get_mid_grayscale_img_names();
	std::vector<std::string> right_names = get_ocv_img_mgr()->get_right_grayscale_img_names();

	for (unsigned int i = 0; i < left_names.size(); ++i)
	{
		std::string name = left_names[i]; 
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

	for (unsigned int i = 0; i < mid_names.size(); ++i)
	{
		std::string name = mid_names[i]; 
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

	for (unsigned int i = 0; i < right_names.size(); ++i)
	{
		std::string name = right_names[i]; 
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