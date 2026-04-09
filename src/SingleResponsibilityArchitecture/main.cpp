//
// Created by moinshaikh on 4/9/26.
//

#include"../../include/SingleResponsibilityArchitecture/filters.hpp"
#include<iostream>

int main(int argc, char* argv[])
{


    try {
        std::string path = "/home/moinshaikh/CLionProjects/Architecturecpp/data/test.png";
        Filters filters(path);
        
        std::cout << "Applying sketch filter..." << std::endl;
        filters.applyAndShowFilter(sketchs);
        
        std::cout << "Applying cartoon filter..." << std::endl;
        filters.applyAndShowFilter(cartoon);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
