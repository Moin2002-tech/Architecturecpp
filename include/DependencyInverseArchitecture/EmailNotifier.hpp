//
// Created by moinshaikh on 4/22/26.
//

#ifndef ARCHITECTURESINC___EMAILNOTIFIER_HPP
#define ARCHITECTURESINC___EMAILNOTIFIER_HPP


#include"Notifier.hpp"


class EmailNotifier : public Notifier {
    public:
        void notify(const std::string & message) override;
    private:
        void sendEmail(const std::string & message);
};
#endif //ARCHITECTURESINC___EMAILNOTIFIER_HPP
