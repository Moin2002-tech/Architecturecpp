//
// Created by moinshaikh on 4/10/26.
//

#include "../../include/OpenAndClosedArchitecture/readers.hpp"
#include<opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // Create image type converters
    GrayScale grayConverter;
    Color colorConverter;
    
    // Create ImageLoader instances with different converters
    // This demonstrates dependency injection - we can inject any ImageType
    ImageLoader grayLoader("/home/moinshaikh/CLionProjects/Architecturecpp/data/test.png", &grayConverter);
    ImageLoader colorLoader("/home/moinshaikh/CLionProjects/Architecturecpp/data/test.png", &colorConverter);
    
    try {
        // Load and process images with different converters
        cv::Mat originalImage = grayLoader.loadImage();
        
        if (!originalImage.empty()) {
            std::cout << "Image loaded successfully!" << std::endl;
            std::cout << "Original image size: " << originalImage.cols << "x" << originalImage.rows << std::endl;
            
            // Process with grayscale converter
            cv::Mat grayImage = grayLoader.processImage();
            std::cout << "Grayscale conversion completed!" << std::endl;
            
            // Process with color converter
            cv::Mat colorImage = colorLoader.processImage();
            std::cout << "Color conversion completed!" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Open/Closed Principle Demo ===" << std::endl;
    std::cout << "The ImageLoader class is closed for modification" << std::endl;
    std::cout << "but open for extension through new ImageType implementations." << std::endl;
    std::cout << "We can add new image processors without changing ImageLoader!" << std::endl;
    
    return 0;
}
