//
// Created by moinshaikh on 4/10/26.
//


#include "../../include/InterfaceSegregationArchitecture/ImageManager.hpp"
#include<stdexcept>

ImageManager::ImageManager(cv::Mat &image, cv::Mat &output) : image_(image), output_(output)
{

}

void ImageManager::save(cv::Mat image, FileFormat format)
{
    if (image.empty())
    {
        throw std::runtime_error("Image is empty");
    }

    if (format == FileFormat::jpeg)
    {
        cv::imwrite("/home/moinshaikh/CLionProjects/Architecturecpp/data/image.jpeg",image);
    }
    else if (format == FileFormat::jpg)
    {
        cv::imwrite("/home/moinshaikh/CLionProjects/Architecturecpp/data/image.jpg",image);
    }
    else if (format == FileFormat::png)
    {
        cv::imwrite("/home/moinshaikh/CLionProjects/Architecturecpp/data/image.png",image);
    }
    else
    {
        throw std::runtime_error("Unknown format");
    }
}


cv::Mat ImageManager::applyFilter(const cv::Mat &image, cv::Mat &output)
{
    cv::cvtColor(image, output, cv::COLOR_BGR2GRAY);
    return output;
}

