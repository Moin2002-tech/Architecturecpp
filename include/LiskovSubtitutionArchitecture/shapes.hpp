//
// Created by moinshaikh on 4/10/26.
//

#ifndef ARCHITECTURESINC___SHAPES_HPP
#define ARCHITECTURESINC___SHAPES_HPP

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

class Shape
{
public:
    virtual void draw(cv::Mat& canvas) = 0;
    virtual void show(const cv::Mat& image, const std::string& windowName) = 0;
    virtual ~Shape() = default;
};



#endif //ARCHITECTURESINC___SHAPES_HPP
