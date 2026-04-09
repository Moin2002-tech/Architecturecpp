//
// Created by moinshaikh on 4/10/26.
//
#include"../../include/OpenAndClosedArchitecture/readers.hpp"
#include<iostream>
#include<opencv2/opencv.hpp>

cv::Mat ImageLoader::loadImage()
{
    image_ = cv::imread(imagePath);
    if (image_.empty())
    {
        std::cerr << "Error: Could not load image from " << imagePath << std::endl;
        return cv::Mat();
    }
    return image_;
}

cv::Mat ImageLoader::processImage()
{
    if (image_.empty())
    {
        loadImage();
    }
    
    if (converter && !image_.empty())
    {
        return converter->convert(image_);
    }
    
    return image_;
}

cv::Mat GrayScale::convert(const cv::Mat& image)
{
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    return grayImage;
}

cv::Mat Color::convert(const cv::Mat& image)
{
    cv::Mat colorImage;
    cv::cvtColor(image, colorImage, cv::COLOR_BGR2RGB);
    return colorImage;
}