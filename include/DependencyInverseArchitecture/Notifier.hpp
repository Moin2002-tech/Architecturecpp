//
// Created by moinshaikh on 4/22/26.
//

#ifndef ARCHITECTURESINC___NOTIFIER_HPP
#define ARCHITECTURESINC___NOTIFIER_HPP

#include<iostream>
#include<string>
#include<memory>
class Notifier
{
public:
    virtual ~Notifier() = default;
    virtual void notify(const std::string & message) = 0;
};

#endif //ARCHITECTURESINC___NOTIFIER_HPP
