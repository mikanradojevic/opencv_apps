#include "video_capture.h"

#include "opencv2/opencv_modules.hpp"

c_videocap_manager::c_videocap_manager()
{
	m_ocv_videocaps.reserve(k_num_images);
	
	for (int i = 0; i < k_num_images; ++i) 
	{
		ocv_videocap_ptr videocap = ocv_videocap_ptr(new cv::VideoCapture());
		m_ocv_videocaps.push_back(videocap);
	}
	
	// int num_cams = cvcam
}

c_videocap_manager::~c_videocap_manager() 
{
	for (int i = 0; i < k_num_images; ++i)
		m_ocv_videocaps[i].reset(); 
}

bool c_videocap_manager::open_cam(e_image_idx cam_idx) 
{
	bool is_opened = m_ocv_videocaps[cam_idx]->open(cam_idx);
	return is_opened; 
}

//////////////////////////////////////////////////////////////////////////

c_videocap_manager* get_videocap_mgr() 
{
	static c_videocap_manager videocap_instance; 
	return &videocap_instance; 
}