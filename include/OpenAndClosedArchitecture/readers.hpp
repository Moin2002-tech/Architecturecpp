//
// Created by moinshaikh on 4/10/26.
//

#ifndef ARCHITECTURESINC___READERS_HPP
#define ARCHITECTURESINC___READERS_HPP

#include<opencv2/opencv.hpp>

class ImageType
{
public:
    virtual ~ImageType() = default;
    virtual cv::Mat convert(const cv::Mat& image) = 0;
};

class ImageLoader
{
private:
    std::string imagePath;
    cv::Mat image_;
    ImageType* converter;

public:
    ImageLoader() = default;
    ImageLoader(const std::string& path, ImageType* conv) : imagePath(path), converter(conv) {}
    cv::Mat loadImage();
    cv::Mat processImage();
};

class GrayScale : public ImageType
{
public:
    cv::Mat convert(const cv::Mat& image) override;
};

class Color : public ImageType
{
public:
    cv::Mat convert(const cv::Mat& image) override;
};


#endif //ARCHITECTURESINC___READERS_HPP
