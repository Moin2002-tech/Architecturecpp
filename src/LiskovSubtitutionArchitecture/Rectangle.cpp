//
// Created by moinshaikh on 4/10/26.
//


#include"../../include/LiskovSubtitutionArchitecture/Rectangle.hpp"


Rectangle::Rectangle(const cv::Point& topLeft, const cv::Point& bottomRight, const cv::Scalar& color, int thickness) 
    : topLeft_(topLeft), bottomRight_(bottomRight), color_(color), thickness_(thickness)
{
}

void Rectangle::draw(cv::Mat& canvas)
{
    cv::rectangle(canvas, topLeft_, bottomRight_, color_, thickness_);
}

void Rectangle::show(const cv::Mat &image, const std::string &windowName)
{
    cv::imshow(windowName, image);
    cv::waitKey(0);
}
