//
// Created by moinshaikh on 4/10/26.
//

#ifndef ARCHITECTURESINC___READERS_HPP
#define ARCHITECTURESINC___READERS_HPP
/*
    * The open–closed principle (OCP) states that software entities (such as functions, classes, and modules)
    * are supposed to be both open for extension and closed for modification. Open for extension means that
    * new functionalities can be added without changing the existing code. Closed for modification means
    * existing software entities shouldn’t be changed, as this can often cause bugs elsewhere in the system.
    * Note that this definition of OCP we discussed is slightly different from the more common one related
    * to polymorphism. The latter is about creating base classes that can’t be modified themselves but are
    * open for others to inherit from them.
    * Speaking of polymorphism, let’s move on to the next principle, which uses it correctly.
*/
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
