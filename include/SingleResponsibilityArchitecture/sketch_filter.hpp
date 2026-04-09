//
// Created by moinshaikh on 4/9/26.
//

#ifndef ARCHITECTURESINC___SKETCH_FILTER_HPP
#define ARCHITECTURESINC___SKETCH_FILTER_HPP

#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

class SketchFilter
{
public:
    SketchFilter();
    ~SketchFilter();
    
    cv::Mat apply(const cv::Mat& image);
    
private:
    cv::Mat convertToGrayscale(const cv::Mat& image);
    cv::Mat detectEdges(const cv::Mat& grayImage);
    cv::Mat invertEdges(const cv::Mat& edges);
};

#endif //ARCHITECTURESINC___SKETCH_FILTER_HPP
