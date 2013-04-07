#include <algorithm>
#include <fstream>
#include <sstream>
#include "image.h"
#include "utils.h"

c_ocv_image_manager* get_ocv_img_mgr()
{
	static c_ocv_image_manager instance; 
	return &instance; 
} 

c_ocv_image_manager::c_ocv_image_manager()
{  
}

c_ocv_image_manager::~c_ocv_image_manager()
{	
}

std::string c_ocv_image_manager::add_left_grayscale_image(ocv_mat_ptr img, int rotation_angle)
{
	std::stringstream ss; 
	ss << rotation_angle; 
	std::string name = LEFT_IMAGE_GRAYSCALE_NAME + "-" + ss.str(); 
	std::string new_name = add_image(name, img); 
	
	m_left_image_names.push_back(new_name);
	
	return new_name; 
}

std::string c_ocv_image_manager::add_mid_grayscale_image(ocv_mat_ptr img, int rotation_angle)
{
	std::stringstream ss; 
	ss << rotation_angle; 
	std::string name = MID_IMAGE_GRAYSCALE_NAME + "-" + ss.str(); 
	std::string new_name = add_image(name, img); 

	m_mid_image_names.push_back(new_name);

	return new_name; 
}

std::string c_ocv_image_manager::add_right_grayscale_image(ocv_mat_ptr img, int rotation_angle)
{
	std::stringstream ss; 
	ss << rotation_angle; 
	std::string name = RIGHT_IMAGE_GRAYSCALE_NAME + "-" + ss.str(); 
	std::string new_name = add_image(name, img); 
		
	m_right_image_names.push_back(new_name);
	
	return new_name; 
}

std::string c_ocv_image_manager::add_image(const std::string& name, ocv_mat_ptr img) 
{
	 if (is_image_valid(img))
	 {
		 ocv_mat_ptr found_img = find_image_by_name(name);
		 int img_count = find_image_count_by_name(name); 
		 if (!found_img)
		 {
			 m_image_dict.insert(images_map::value_type(name, img));
			 m_images_count_dict.insert(images_counts_dict::value_type(name, ++img_count));
			 return name; 
		 }
		 else 
		 {
			 std::stringstream ss; 
			 ss << name << "-" << img_count;
			 m_image_dict.insert(images_map::value_type(ss.str(), img));
			 increase_image_count(name); 
			 return ss.str();
		 }
	 } 
	 else
		 return std::string("INVALID_IMG");
}

int c_ocv_image_manager::remvove_image(const std::string& name, ocv_mat_ptr img) 
{
	if (is_image_valid(img))
	{
		ocv_mat_ptr found_img = find_image_by_name(name); 
		if (is_image_valid(img)) 
		{
			m_image_dict.erase(name); 
		}
	}
	return m_image_dict.size(); 
}

ocv_mat_ptr c_ocv_image_manager::find_image_by_name(const std::string& name)
{
	images_map::iterator it = m_image_dict.find(name);
	if (it != m_image_dict.end()) 
		return it->second; 
	else 
		return ocv_mat_ptr(); 
}

int c_ocv_image_manager::find_image_count_by_name(const std::string& name)
{
	images_counts_dict::iterator it = m_images_count_dict.find(name); 
	if (it != m_images_count_dict.end())
		return it->second; 
	else 
		return 0;
}

void c_ocv_image_manager::increase_image_count(const std::string& name)
{
	images_counts_dict::iterator it = m_images_count_dict.find(name); 
	if (it != m_images_count_dict.end())
		(it->second)++;
}

////////////////////////////////////////////////////////////////////////// 

ocv_mat_ptr make_ocv_image(unsigned int width, unsigned int height, int flag)
{
	ocv_mat_ptr img; 
	img.reset(new cv::Mat(width, height, flag));

	return img;
}

void delete_ocv_image(ocv_mat_ptr& img)
{
	if (img != ocv_mat_ptr())
	{
		ptr_delete(img);
	}
}

ocv_mat_ptr resize_image(ocv_mat_ptr& src_img, cv::Size& size, int interpolation /* = cv::INTER_LINEAR */) 
{
	assert(!is_ptr_null(src_img) && src_img->data);
	ocv_mat_ptr dest_img = ocv_mat_ptr(new cv::Mat(*src_img));
	assert(dest_img->data);

	cv::resize(*src_img, *dest_img, size, 0.0, 0.0, interpolation);
	assert(dest_img->data); 

	return dest_img; 
}

ocv_mat_ptr calc_hist(ocv_mat_ptr& src_img)
{ 
	int hist_size = 256;
	float range[] = {0, 256};
	const float *hist_range = {range}; 

	cv::Mat hist(256, 1, CV_8UC1);
	bool uniform = true; 
	bool accum = false;
	cv::calcHist(get_ptr_raw(src_img), 1, 0, cv::Mat(), hist, 1, &hist_size, &hist_range, uniform, accum); 

	ocv_mat_ptr hist_mat = ocv_mat_ptr(new cv::Mat(hist)); 

	std::ofstream ofs("hist_debug.txt"); 
	ofs << "hist mat: " << hist; 
	ofs.close();
  
	return hist_mat;  
}

struct pixel_pos 
{
	int x, y; 
	pixel_pos(int _x, int _y)
		:x(_x), y(_y) {} 
}; 

void calc_mtf(ocv_mat_ptr& image, const cv::Point2i& p1, const cv::Point2i& p2, mtf_data_vec& mtf_data)
{
	if (!is_image_valid(image))
		return;
	if ( p1.x < 0 || p2.x > image->cols || p1.y < 0 || p2.y > image->rows) 
		return; 
	
	cv::Point2i tp1 = p1;
	cv::Point2i tp2 = p2;
	std::vector<pixel_pos> pixel_pos_vec;
	int x1 = p1.x; 
	int y1 = p1.y; 
	int x2 = p2.x; 
	int y2 = p2.y; 
	int dx = std::abs(x2 - x1); 
	int dy = std::abs(y2 - y1);
	int x = 0;
	int y = 0;
	int temp1 = 2 * dy; 
	int temp2 = 2 * (dy - dx); 
	int p = temp1 - dx; 
	if (p1.x > p2.x) 
		std::swap(tp1, tp2); 
	x = tp1.x;
	y = tp1.y; 
	x2 = tp2.x;

	int y_step = (tp1.y < tp2.y) ? 1 : -1; 

	while (x < x2)
	{
		x++; 
		if (p < 0) 
			p += temp1; 
		else 
		{
			y += y_step;
			p += temp2; 
		}
		
		pixel_pos_vec.push_back(pixel_pos(x, y)); 
	}	
	wx_log_message("start : %d, %d | end : %d, %d", p1.x, p1.y, p2.x, p2.y);
	for (unsigned int i = 0; i < pixel_pos_vec.size(); ++i)
	{ 	
		int x = pixel_pos_vec[i].x; 
		int y = pixel_pos_vec[i].y; 
		int pos = y * image->cols + x; 

		wx_log_message("x : %d | y : %d", x, y);
		if (x < 0 || x >= image->cols || y < 0  || y >= image->rows)
			continue;
		unsigned char *pixel_ptr = (unsigned char*)(image->data);
		float pixel_value = (float)((float)pixel_ptr[pos] / 255);
		mtf_data.push_back(pixel_value);
	}
}

bool is_image_valid(ocv_mat_ptr& img) 
{
	return (img != ocv_mat_ptr()); 
} 

int hist_mat_to_vector(ocv_mat_ptr hist, hist_data_vec& hist_vec)
{
	if (is_ptr_null(hist))
		return -1;  

	hist_vec.clear(); 

	size_t elem_size = hist->elemSize();
	int elem_depth = hist->depth();

	for(int i = 0; i < hist->rows; ++i)
	{	
		float *pv = hist->ptr<float>(i); 
		hist_vec.push_back((int)*pv); 
	} 
	
	return (int)(hist_vec.size()); 
} 