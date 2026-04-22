//
// Created by moinshaikh on 4/22/26.
//



#include"../../include/DependencyInverseArchitecture/NotificationSystem.hpp"


void NotificationSystem::notify(const std::string &message)
{
    for (const auto& notifer : _notifier)
    {

        notifer->notify(message);
    }

}