//
// Created by moinshaikh on 4/26/26.
//


#include"../../include/StatefulArchitectureAndStateLessArchitecture/StatefulArchitecture.h"
#include"../../include/StatefulArchitectureAndStateLessArchitecture/StateLessArchitecture.hpp"
#include<drogon/drogon.h>
#include<iostream>


int main()
{
    drogon::app()
        .loadConfigFile("/home/moinshaikh/CLionProjects/Architecturecpp/data/config.json")
        .enableSession(1200)   // ← add this as a safety net alongside config
        .run();
}