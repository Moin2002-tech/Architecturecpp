//
// Created by moinshaikh on 4/22/26.
//
#include"../../include/DependencyInverseArchitecture/EmailNotifier.hpp"


void EmailNotifier::notify(const std::string &message)
{
    sendEmail(message);
}

void EmailNotifier::sendEmail(const std::string &message)
{
    std::cout << "Sending email: " << message << std::endl;
}

