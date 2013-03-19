#ifndef __VIDEO_CAPTURE_H__
#define __VIDEO_CAPTURE_H__

#include "opencv2/opencv.hpp"
#include "prerequisites.h"

typedef boost::shared_ptr<cv::VideoCapture> ocv_videocap_ptr; 

class c_videocap_manager 
{
public: 
	c_videocap_manager(); 
	~c_videocap_manager(); 
	
	bool open_cam(e_image_idx idx); 
	ocv_videocap_ptr get_ocv_videocap(e_image_idx idx); 

private: 
	std::vector<ocv_videocap_ptr> m_ocv_videocaps; 
};
 
extern c_videocap_manager* get_videocap_mgr(); 

#endif