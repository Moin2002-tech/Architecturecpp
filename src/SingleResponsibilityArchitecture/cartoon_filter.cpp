//
// Created by moinshaikh on 4/9/26.
//

#include"../../include/SingleResponsibilityArchitecture/cartoon_filter.hpp"

CartoonFilter::CartoonFilter()
{
}

CartoonFilter::~CartoonFilter()
{
}

cv::Mat CartoonFilter::apply(const cv::Mat& image)
{
    cv::Mat smooth = applyBilateralSmoothing(image);
    cv::Mat edges = detectEdges(image);
    return combineSmoothAndEdges(smooth, edges);
}

cv::Mat CartoonFilter::applyBilateralSmoothing(const cv::Mat& image)
{
    cv::Mat smooth = image.clone();
    for (int i = 0; i < 5; i++) {
        cv::Mat temp;
        cv::bilateralFilter(smooth, temp, 9, 150, 150);
        smooth = temp.clone();
    }
    return smooth;
}

cv::Mat CartoonFilter::detectEdges(const cv::Mat& image)
{
    cv::Mat gray, blurred, edges, edgesBinary, edgesInv;
    
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::medianBlur(gray, blurred, 5);
    cv::Laplacian(blurred, edges, CV_8U, 5);
    cv::threshold(edges, edgesBinary, 60, 255, cv::THRESH_BINARY);
    cv::bitwise_not(edgesBinary, edgesInv);
    
    return edgesInv;
}

cv::Mat CartoonFilter::combineSmoothAndEdges(const cv::Mat& smooth, const cv::Mat& edges)
{
    cv::Mat edgesBGR, cartoonImage;
    cv::cvtColor(edges, edgesBGR, cv::COLOR_GRAY2BGR);
    cv::bitwise_and(smooth, edgesBGR, cartoonImage);
    return cartoonImage;
}
