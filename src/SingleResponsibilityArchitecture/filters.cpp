//
// Created by moinshaikh on 4/9/26.
//


#include"../../include/SingleResponsibilityArchitecture/filters.hpp"
#include<iostream>

Filters::Filters(const std::string& path) : loader(path)
{
}



Filters::~Filters()
{
}

void Filters::applyAndShowFilter(enum Filter filter)
{
    try {
        cv::Mat image = loader.loadImage();
        
        if (filter == sketchs) {
            cv::Mat sketchResult = sketchFilter.apply(image);
            display.showImageAndWait(sketchResult, "Sketch");
        }
        else if (filter == cartoon) {
            cv::Mat cartoonResult = cartoonFilter.apply(image);
            display.showImageAndWait(cartoonResult, "Cartoon");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

cv::Mat Filters::getCurrentImage() const
{
    try
        {
        return const_cast<ImageLoader&>(loader).loadImage();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return cv::Mat();
    }
}

