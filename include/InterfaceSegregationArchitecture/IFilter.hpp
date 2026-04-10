//
// Created by moinshaikh on 4/10/26.
//

#ifndef ARCHITECTURESINC___IFILTER_HPP
#define ARCHITECTURESINC___IFILTER_HPP
#include<opencv2/opencv.hpp>
class IFilter
{
public:
    virtual ~IFilter() = default;
    virtual cv::Mat applyFilter(const cv::Mat &image, cv::Mat &output) = 0;
};

#endif //ARCHITECTURESINC___IFILTER_HPP
