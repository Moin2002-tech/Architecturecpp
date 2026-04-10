//
// Created by moinshaikh on 4/10/26.
//


#include"../../include/LiskovSubtitutionArchitecture/Circle.hpp"


Circle::Circle(const cv::Point& center, int radius, const cv::Scalar& color) : center_(center), radius_(radius), color_(color)
{
}

void Circle::draw(cv::Mat& canvas) {
    cv::circle(canvas, center_, radius_, color_);
}

void Circle::show(const cv::Mat& image, const std::string& windowName)
{
    cv::imshow(windowName, image);
    cv::waitKey(0);
}





