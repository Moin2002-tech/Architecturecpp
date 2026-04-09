//
// Created by moinshaikh on 4/9/26.
//

#include"../../include/SingleResponsibilityArchitecture/image_loader.hpp"
#include<fstream>

ImageLoader::ImageLoader(const std::string& path) : imagePath(path)
{
}

ImageLoader::~ImageLoader()
{

}

cv::Mat ImageLoader::loadImage()
{
    if (!validatePath()) {
        throw std::runtime_error("Invalid image path: " + imagePath);
    }
    
    cv::Mat image = cv::imread(imagePath);
    if (image.empty())
    {
        throw std::runtime_error("Failed to load image: " + imagePath);
    }
    
    return image;
}

bool ImageLoader::validatePath() const
{
    std::ifstream file(imagePath);
    return file.good();
}

void ImageLoader::setPath(const std::string& path)
{
    imagePath = path;
}

std::string ImageLoader::getPath() const
{
    return imagePath;
}
