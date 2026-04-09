//
// Created by moinshaikh on 4/9/26.
//

#include"../../include/SingleResponsibilityArchitecture/image_display.hpp"

ImageDisplay::ImageDisplay()
{
}

ImageDisplay::~ImageDisplay()
{
    closeAllWindows();
}

void ImageDisplay::showImage(const cv::Mat& image, const std::string& windowName)
{
    if (!image.empty()) {
        cv::imshow(windowName, image);
    }
}

void ImageDisplay::showImageAndWait(const cv::Mat& image, const std::string& windowName)
{
    showImage(image, windowName);
    cv::waitKey(0);
}

void ImageDisplay::closeAllWindows()
{
    cv::destroyAllWindows();
}
