//
// Created by moinshaikh on 4/22/26.
//

#ifndef ARCHITECTURESINC___NOTIFICATIONSYSTEM_HPP
#define ARCHITECTURESINC___NOTIFICATIONSYSTEM_HPP

#include"Notifier.hpp"
#include<vector>
class NotificationSystem : public Notifier {

public:
    using Notifiers =  std::vector<std::unique_ptr<Notifier>>;

    explicit NotificationSystem(Notifiers notifier) : _notifier(std::move(notifier)) {}

    void notify(const std::string & message) override;
private:
    Notifiers _notifier;
};

#endif //ARCHITECTURESINC___NOTIFICATIONSYSTEM_HPP
