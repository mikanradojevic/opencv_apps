#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>
#include <map> 
#include "boost/shared_ptr.hpp"
#include "opencv2/opencv.hpp" 
#include "prerequisites.h"

int hist_mat_to_vector(ocv_mat_ptr hist, hist_data_vec& hist_vec); 
ocv_mat_ptr equalize_hist(ocv_mat_ptr src_hist); 

class c_ocv_image_manager
{
public: 
	c_ocv_image_manager();
	~c_ocv_image_manager();

	ocv_mat_ptr new_greyscale_img(e_image_idx img_idx, int width, int height); 

	ocv_mat_ptr load_from_file(const std::string& file_name, e_image_idx idx, int flag = CV_LOAD_IMAGE_GRAYSCALE); 
	void unload(e_image_idx idx); 
	void release_all() {}; 
	ocv_mat_ptr resize_img(e_image_idx img, cv::Size& size, int interpolation = cv::INTER_LINEAR); 
	ocv_mat_ptr calc_grayscale_hist(e_image_idx idx); 
	void calc_mtf(e_image_idx idx, const cv::Point2i& p1, const cv::Point2i& p2, mtf_data_vec& mtf_data);
	
	
	bool is_image_valid(e_image_idx idx) 
	{
		return !(is_ptr_null(m_grayscale_imgs[idx])); 
	}

	ocv_mat_ptr get_grayscale_img(e_image_idx idx);
	ocv_mat_ptr get_hist(e_image_idx idx);
	
private: 
	
	std::vector<std::string> m_img_paths;
	std::vector<ocv_mat_ptr> m_grayscale_imgs;
	std::vector<ocv_mat_ptr> m_hists; 
};

extern c_ocv_image_manager* get_ocv_img_mgr(); 

#endif