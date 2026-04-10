//
// Created by moinshaikh on 4/10/26.
//

#ifndef ARCHITECTURESINC___CIRCLE_HPP
#define ARCHITECTURESINC___CIRCLE_HPP

#include"shapes.hpp"

class Circle : public Shape
{
private:
    cv::Point center_;
    int radius_;
    cv::Scalar color_;
public:
    Circle(const cv::Point& center, int radius, const cv::Scalar& color);
    void draw(cv::Mat& canvas) override;
    void show(const cv::Mat& image, const std::string& windowName) override;
    ~Circle() = default;

};

#endif //ARCHITECTURESINC___CIRCLE_HPP
