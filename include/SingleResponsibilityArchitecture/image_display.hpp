//
// Created by moinshaikh on 4/9/26.
//

#ifndef ARCHITECTURESINC___IMAGE_DISPLAY_HPP
#define ARCHITECTURESINC___IMAGE_DISPLAY_HPP

#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>

class ImageDisplay
{
public:
    ImageDisplay();
    ~ImageDisplay();
    
    void showImage(const cv::Mat& image, const std::string& windowName);
    void showImageAndWait(const cv::Mat& image, const std::string& windowName);
    void closeAllWindows();
};

#endif //ARCHITECTURESINC___IMAGE_DISPLAY_HPP
