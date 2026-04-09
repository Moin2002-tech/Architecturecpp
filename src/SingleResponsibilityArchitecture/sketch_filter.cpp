//
// Created by moinshaikh on 4/9/26.
//

#include"../../include/SingleResponsibilityArchitecture/sketch_filter.hpp"

SketchFilter::SketchFilter()
{
}

SketchFilter::~SketchFilter()
{
}

cv::Mat SketchFilter::apply(const cv::Mat& image)
{
    cv::Mat grayImage = convertToGrayscale(image);
    cv::Mat edges = detectEdges(grayImage);
    return invertEdges(edges);
}

cv::Mat SketchFilter::convertToGrayscale(const cv::Mat& image)
{
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

cv::Mat SketchFilter::detectEdges(const cv::Mat& grayImage)
{
    cv::Mat blurred, edges, edgesBinary;
    
    cv::medianBlur(grayImage, blurred, 5);
    cv::Laplacian(blurred, edges, CV_8U, 5);
    cv::threshold(edges, edgesBinary, 100, 255, cv::THRESH_BINARY);
    
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2));
    cv::dilate(edgesBinary, edgesBinary, kernel);
    
    return edgesBinary;
}

cv::Mat SketchFilter::invertEdges(const cv::Mat& edges)
{
    cv::Mat output;
    cv::bitwise_not(edges, output);
    return output;
}
