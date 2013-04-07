#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>
#include <map> 
#include "boost/shared_ptr.hpp"
#include "opencv2/opencv.hpp" 
#include "prerequisites.h"

/**,
	OpenCV image maintainer 
	Ocv image includes RGB/Grayscale images, histogram and other data matrix 
*/

const std::string LEFT_IMG = "left_image"; 
const std::string MID_IMG = "mid_image"; 
const std::string RIGHT_IMG = "right_image"; 

const int DEFAULT_IMG_SiZE = 1; 

class c_ocv_image_manager
{
	typedef std::map<std::string, ocv_mat_ptr> images_map;
	typedef std::map<std::string, ocv_mat_ptr> hist_map;  
	typedef std::map<std::string, int> images_counts_dict; 
	
public: 
	c_ocv_image_manager();
	~c_ocv_image_manager();
 
	std::string add_left_grayscale_image(ocv_mat_ptr img, int rotation_angle);
	std::string add_mid_grayscale_image(ocv_mat_ptr img, int rotation_angle);
	std::string add_right_grayscale_image(ocv_mat_ptr img, int rotation_angle); 
	
	// Add an image to the manager
	std::string add_image(const std::string& name, ocv_mat_ptr img); 
	// Remove an image 
	int remvove_image(const std::string& name, ocv_mat_ptr img); 
	// Find an image
	ocv_mat_ptr find_image_by_name(const std::string& name); 
	int find_image_count_by_name(const std::string& name);
	void increase_image_count(const std::string& name); 

	std::vector<std::string> get_left_grayscale_img_names() const { return m_left_image_names; }
	std::vector<std::string> get_mid_grayscale_img_names() const { return m_mid_image_names; }
	std::vector<std::string> get_right_grayscale_img_names() const { return m_right_image_names; }

private:  
	
	images_map m_image_dict; 
	hist_map m_hist_dict; 
	images_counts_dict m_images_count_dict; 
	
	std::vector<std::string> m_left_image_names; 
	std::vector<std::string> m_mid_image_names;
	std::vector<std::string> m_right_image_names;
 

};
extern c_ocv_image_manager* get_ocv_img_mgr(); 

/////////////////////////////////////////////////////////////////////////

// Create an empty ocv image 
ocv_mat_ptr make_ocv_image(unsigned int width, unsigned int height, int flag = CV_8UC1);

// Delete an image from memory 
void delete_ocv_image(ocv_mat_ptr& img);

// Resize the image
ocv_mat_ptr resize_image(ocv_mat_ptr& src_img, cv::Size& size, int interpolation = cv::INTER_LINEAR);

// Calcuate the histogram 
ocv_mat_ptr calc_hist(ocv_mat_ptr& src_img);

// Calculate MTF
void calc_mtf(ocv_mat_ptr& image, const cv::Point2i& p1, const cv::Point2i& p2, mtf_data_vec& mtf_data); 

// Check an image	
bool is_image_valid(ocv_mat_ptr& img);  

// 
int hist_mat_to_vector(ocv_mat_ptr hist, hist_data_vec& hist_vec); 

ocv_mat_ptr equalize_hist(ocv_mat_ptr src_hist); 

#endif