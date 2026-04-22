//
// Created by moinshaikh on 4/10/26.
//

#include "../../include/InterfaceSegregationArchitecture/ImageManager.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    try {
        // Load the test image
        cv::Mat testImage = cv::imread("/home/moinshaikh/CLionProjects/Architecturecpp/data/test.png");
        if (testImage.empty())
        {
            throw std::runtime_error("Failed to load data/test.png");
        }
        
        cv::Mat outputImage;
        
        // Create ImageManager instance
        ImageManager manager(testImage, outputImage);
        
        std::cout << "Testing Interface Segregation Architecture\n";
        std::cout << "========================================\n";
        
        // Test image properties
        std::cout << "Original image size: " << testImage.rows << "x" << testImage.cols << std::endl;
        std::cout << "Original image channels: " << testImage.channels() << std::endl;
        
        // Test filter application
        std::cout << "\nApplying grayscale filter..." << std::endl;
        cv::Mat filteredImage = manager.applyFilter(testImage, outputImage);
        manager.save(filteredImage, FileFormat::png);
        std::cout << "Filtered image size: " << filteredImage.rows << "x" << filteredImage.cols << std::endl;
        std::cout << "Filtered image channels: " << filteredImage.channels() << std::endl;
        
        // Test file saving
        std::cout << "\nTesting file saving..." << std::endl;
        manager.save(testImage, FileFormat::png);
        std::cout << "Saved as PNG" << std::endl;
        
        manager.save(testImage, FileFormat::jpg);
        std::cout << "Saved as JPG" << std::endl;
        
        manager.save(testImage, FileFormat::jpeg);
        std::cout << "Saved as JPEG" << std::endl;
        
        std::cout << "\nAll tests completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
