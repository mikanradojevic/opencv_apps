#include "image.h"



c_ocv_image_manager::c_ocv_image_manager()
{
	m_origin_imgs.reserve(k_num_images); 
	m_hist.reserve(k_num_images); 
}

c_ocv_image_manager::~c_ocv_image_manager()
{
	release_all(); 
}

ocv_mat_ptr c_ocv_image_manager::load_from_file(const std::string& file_name, e_image_idx idx, int flag)
{
	if (!is_image_valid(idx))
	{
		unload(idx); 
	}
	
	cv::Mat temp = cv::imread(file_name.c_str(), flag); 
	ocv_mat_ptr new_mat = ocv_mat_ptr(new cv::Mat(temp));
	if (!new_mat->data)
	{
		new_mat->release(); 
		return ocv_mat_ptr(); 
	}

	m_origin_imgs[idx] = new_mat;
	calculate_hist(idx); 

	return new_mat; 
}

void c_ocv_image_manager::unload(e_image_idx idx)
{
	if (is_image_valid(idx))
	{
		m_origin_imgs[idx].delete_obj();
		m_hist[idx].delete_obj(); 
	}
}

void c_ocv_image_manager::calculate_hist(e_image_idx idx)
{
	int hist_size = 256;
	float range[] = {0, 256};
	const float *hist_range = {range}; 
	
	cv::Mat hist;
	bool uniform = true; 
	bool accum = false;
	cv::calcHist(m_origin_imgs[idx].obj, 1, 0, cv::Mat(), hist, 1, &hist_size, &hist_range, uniform, accum); 

	ocv_mat_ptr hist_mat = ocv_mat_ptr(new cv::Mat(hist)); 
	m_hist[idx] = hist_mat; 
}

//////////////////////////////////////////////////////////////////////////


int hist_mat_to_vector(ocv_mat_ptr hist, hist_data_vec& hist_vec)
{
	if (hist.empty())
		return -1; 

	hist_vec.clear(); 
	
	return (int)(hist_vec.size()); 
}