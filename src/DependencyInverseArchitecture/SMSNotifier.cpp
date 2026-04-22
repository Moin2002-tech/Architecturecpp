//
// Created by moinshaikh on 4/22/26.
//
#include"../../include/DependencyInverseArchitecture/SMSNotifier.hpp"
void SMSNotifier::notify(const std::string & message)
{
    sendSMS(message);
}

void SMSNotifier::sendSMS(const std::string & message)
{
    std::cout << "Sending SMS: " << message << std::endl;
}

