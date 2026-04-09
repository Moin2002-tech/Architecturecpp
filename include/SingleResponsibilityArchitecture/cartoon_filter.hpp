//
// Created by moinshaikh on 4/9/26.
//

#ifndef ARCHITECTURESINC___CARTOON_FILTER_HPP
#define ARCHITECTURESINC___CARTOON_FILTER_HPP

#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

class CartoonFilter
{
public:
    CartoonFilter();
    ~CartoonFilter();
    
    cv::Mat apply(const cv::Mat& image);
    
private:
    cv::Mat applyBilateralSmoothing(const cv::Mat& image);
    cv::Mat detectEdges(const cv::Mat& image);
    cv::Mat combineSmoothAndEdges(const cv::Mat& smooth, const cv::Mat& edges);
};

#endif //ARCHITECTURESINC___CARTOON_FILTER_HPP
