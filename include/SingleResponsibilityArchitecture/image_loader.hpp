//
// Created by moinshaikh on 4/9/26.
//

#ifndef ARCHITECTURESINC___IMAGE_LOADER_HPP
#define ARCHITECTURESINC___IMAGE_LOADER_HPP

#include<opencv2/opencv.hpp>
#include<opencv2/imgcodecs.hpp>

class ImageLoader
{
private:
    std::string imagePath;
    
public:
    ImageLoader(const std::string& path);
    ~ImageLoader();
    
    cv::Mat loadImage();
    bool validatePath() const;
    void setPath(const std::string& path);
    std::string getPath() const;
};

#endif //ARCHITECTURESINC___IMAGE_LOADER_HPP
