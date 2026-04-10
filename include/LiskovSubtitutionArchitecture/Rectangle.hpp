//
// Created by moinshaikh on 4/10/26.
//

#ifndef ARCHITECTURESINC___RECTANGLE_HPP
#define ARCHITECTURESINC___RECTANGLE_HPP
#include"shapes.hpp"
class Rectangle : public Shape {
private:
    cv::Point topLeft_;
    cv::Point bottomRight_;
    cv::Scalar color_;
    int thickness_;
public:
    Rectangle(const cv::Point& topLeft, const cv::Point& bottomRight, const cv::Scalar& color, int thickness = 1);
    void draw(cv::Mat& canvas) override;
    void show(const cv::Mat& image, const std::string& windowName) override;
    ~Rectangle() = default;
};

#endif //ARCHITECTURESINC___RECTANGLE_HPP
