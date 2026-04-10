//
// Created by moinshaikh on 4/10/26.
//

#ifndef ARCHITECTURESINC___IFILE_HPP
#define ARCHITECTURESINC___IFILE_HPP

#include<opencv2/opencv.hpp>
enum class FileFormat
{
    png,
    jpg,
    jpeg
};

class IFile
{
public:
    virtual ~IFile() = default;
    virtual void save(cv::Mat image, FileFormat format) = 0;
};
#endif //ARCHITECTURESINC___IFILE_HPP
