//
// Created by moinshaikh on 4/22/26.
//

#ifndef ARCHITECTURESINC___SMSNOTIFIER_HPP
#define ARCHITECTURESINC___SMSNOTIFIER_HPP
#include"Notifier.hpp"

class SMSNotifier : public Notifier
{
    public:
        void notify(const std::string & message) override;
private:
    void sendSMS(const std::string & message);
};

#endif //ARCHITECTURESINC___SMSNOTIFIER_HPP
