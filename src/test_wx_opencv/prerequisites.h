#ifndef __PREREQUISITES_H__
#define __PREREQUISITES_H__

#include <vector>
#include "boost/shared_ptr.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp" 

typedef std::vector<int> hist_data_vec;  
typedef cv::Ptr<cv::Mat> ocv_mat_ptr; 
#endif