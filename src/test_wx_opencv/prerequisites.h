#ifndef __PREREQUISITES_H__
#define __PREREQUISITES_H__

#define HIGHESTID 5999

#define wxID_OVERVIEW_IMG_PANEL (HIGHESTID+100)
#define wxID_OVERVIEW_GRAPH_PANEL_HIST (HIGHESTID+101)
#define wxID_OVERVIEW_GRAPH_PANEL_MTF (HIGHESTID+102)
#define wxID_OVERVIEW_FRAME (HIGHESTID+103)
#define wxID_OVERVIEW_CAM_FRAME (HIGHESTID+104) 
#define wxID_IMAGE_FRAME (HIGHESTID+105)

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

const std::string LEFT_IMAGE_ORIGINAL_NAME = "left_image_original";
const std::string MID_IMAGE_ORIGINAL_NAME = "mid_image_original"; 
const std::string RIGHT_IMAGE_ORIGINAL_NAME = "right_image_original";
const std::string LEFT_IMAGE_GRAYSCALE_NAME = "left_image_grayscale"; 
const std::string MID_IMAGE_GRAYSCALE_NAME = "mid_image_grayscale";
const std::string RIGHT_IMAGE_GRAYSCALE_NAME = "right_image_grayscale"; 

typedef std::vector<unsigned int> hist_data_vec;  
typedef std::vector<float> mtf_data_vec; 

// typedef cv::Ptr<cv::Mat> ocv_mat_ptr;
typedef boost::shared_ptr<cv::Mat> ocv_mat_ptr; 

#define is_ptr_null(ptr) (!(ptr))
#define get_ptr_raw(ptr) ((ptr).get())
#define ptr_delete(ptr) ((ptr).reset())

#endif