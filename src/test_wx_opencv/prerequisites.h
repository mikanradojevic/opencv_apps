#ifndef __PREREQUISITES_H__
#define __PREREQUISITES_H__

#define HIGHESTID 5999

#define wxID_OVERVIEW_IMG_PANEL (HIGHESTID+100)
#define wxID_OVERVIEW_GRAPH_PANEL (HIGHESTID+101)
#define wxID_OVERVIEW_FRAME (HIGHESTID+102)
#define wxID_OVERVIEW_CAM_FRAME (HIGHESTID+103)

#include <vector>
#include "boost/shared_ptr.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp" 

enum e_image_idx
{
	k_left_image = 0, 
	k_mid_image = 1,
	k_right_image = 2,
	k_num_images = 3
};  

typedef std::vector<unsigned int> hist_data_vec;  
typedef std::vector<unsigned char> mtf_data_vec; 

// typedef cv::Ptr<cv::Mat> ocv_mat_ptr;
typedef boost::shared_ptr<cv::Mat> ocv_mat_ptr; 

#define is_ptr_null(ptr) (!(ptr))
#define get_ptr_raw(ptr) ((ptr).get())
#define ptr_delete(ptr) ((ptr).reset())

#endif