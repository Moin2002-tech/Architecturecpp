//
// Created by moinshaikh on 4/10/26.
//

#ifndef ARCHITECTURESINC___IMAGEMANAGER_HPP
#define ARCHITECTURESINC___IMAGEMANAGER_HPP

#include"IFile.hpp"
#include"IFilter.hpp"


class ImageManager : public IFile, IFilter
{
private:
    cv::Mat image_;
    cv::Mat output_;
public:
    ImageManager() = default;
    ImageManager(cv::Mat &image, cv::Mat &output);
    void save(cv::Mat image, FileFormat format) override;

    cv::Mat applyFilter(const cv::Mat &image, cv::Mat &output) override;

    cv::Mat getImage() const { return image_; }
    cv::Mat getOutput() const { return output_; }


};

#endif //ARCHITECTURESINC___IMAGEMANAGER_HPP
