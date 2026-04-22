//
// Created by moinshaikh on 4/22/26.
//

#include<iostream>
#include"../../include/DependencyInverseArchitecture/EmailNotifier.hpp"
#include"../../include/DependencyInverseArchitecture/SMSNotifier.hpp"
#include"../../include/DependencyInverseArchitecture/NotificationSystem.hpp"
/*
 *
 * Dependency inversion principle
    Dependency inversion is a principle useful for decoupling by inverting the dependency relationship.
    In essence, it means that high-level modules should not depend on lower-level ones. Instead, both
    should depend on the same abstraction because classes should not rely on the implementation details
    of their dependencies.
    C++ allows two ways to invert the dependencies between your classes. The first one is the regular
    polymorphic approach, and the second uses templates. Let’s see how to apply both of them in practice.
    Assume you’re modeling a notification system that is supposed to have SMS and email channels. A
    simple approach would be to write it like so:
    class SMSNotifier {
    public:
    void sendSMS(const std::string &message) {
    std::cout << "SMS channel: " << message << std::endl;
    }
    };
    class EMailNotifier {
    public:
    void sendEmail(const std::string &message) {
    std::cout << "Email channel: " << message << std::endl;
    }
    };
    class NotificationSystem {
    public:
    void notify(const std::string &message) {
    sms_.sendSMS(message);
    email_.sendEmail(message);
    }
    private:Chapter 1
    23
    SMSNotifier sms_;
    EMailNotifier email_;
    };
    Each notifier is constructed by the NotificationSystem class. This approach is not ideal, though,
    since now the higher-level concept, NotificationSystem, depends on lower-level ones—modules for
    individual notifiers. Let’s see how applying dependency inversion using polymorphism changes this.
    We can define our notifiers to depend on an interface as follows:
    class Notifier {
    public:
    virtual ~Notifier() = default;
    virtual void notify(const std::string &message) = 0;
    };
    class SMSNotifier : public Notifier {
    public:
    void notify(const std::string &message) override { sendSMS(message); }
    private:
    void sendSMS(const std::string &message) {
    std::cout << "SMS channel: " << message << std::endl;
    }
    };
    class EMailNotifier : public Notifier {
    public:
    void notify(const std::string &message) override { sendEmail(message); }
    private:
    void sendEmail(const std::string &message) {
    std::cout << "Email channel: " << message << std::endl;
    }
    };
    Now, the NotificationSystem class no longer has to know the implementations of the notifiers. Be-
    cause of this, it has to accept them as constructor arguments:
    class NotificationSystem {
    public:
    using Notifiers = std::vector<std::unique_ptr<Notifier>>;
    explicit NotificationSystem(Notifiers notifiers)Importance of Software Architecture and Principles of Great Design
  
    : notifiers_{std::move(notifiers)} {}
    void notify(const std::string &message) {
    for (const auto &notifier : notifiers_) {
    notifier->notify(message);
    }
    }
    private:
    Notifiers notifiers_;
    };
    In this approach, NotificationSystem is decoupled from the concrete implementations and instead
    depends only on the polymorphic interface named Notifier. The lower-level concrete classes also
    depend on this interface. This can help you shorten your build time and allows for much easier unit
    testing; now, you can easily pass mocks as arguments in your test code.
    Using dependency inversion with virtual dispatch comes at a cost, however, as now we’re dealing with
    memory allocations, and the dynamic dispatch has overhead on its own. Sometimes, C++ compilers can
    detect that only one implementation is being used for a given interface and will remove the overhead
    by performing devirtualization (often, you need to mark the function as final for this to work). Here,
    however, two implementations are used, so the performance cost of dynamic dispatch (commonly
    implemented as jumping through virtual method tables, or vtables for short) must be paid.
    There is another way of inverting dependencies that doesn’t have those drawbacks. Let’s see how this
    can be done using a variadic template from C++11, a generic lambda from C++14, and variant, either
    from C++17 or a third-party library such as Abseil or Boost.
    If you’re not familiar with variant, it’s just a class that can hold any of the types passed as template
    parameters. Because we’re using a variadic template that can have any number of parameters, we can
    pass however many types we like. To call a function on the object stored in the variant, we can either
    extract it using std::get or use std::visit and a callable object—in our case, the generic lambda. It
    shows how duck-typing looks in practice.
    First are the notifier classes:
    class SMSNotifier {
    public:
    void notify(const std::string &message) { sendSMS(message); }
    private:
    void sendSMS(const std::string &message) {
    std::cout << "SMS channel: " << message << std::endl;
    }
    };

    class EMailNotifier {
    public:
    void notify(const std::string &message) { sendEmail(message); }
    private:
    void sendEmail(const std::string &message) {
    std::cout << "Email channel: " << message << std::endl;
    }
    };
    Now, we don’t rely on an interface anymore, so no virtual dispatch will be done. The NotificationSystem
    class will still accept a vector of Notifiers:
    template <typename... T>
    class NotificationSystem {
    public:
    using Notifiers = std::vector<std::variant<T...>>;
    explicit NotificationSystem(Notifiers notifiers)
    : notifiers_{std::move(notifiers)} {}
    void notify(const std::string &message) {
    for (auto &notifier : notifiers_) {
    std::visit([&](auto &n) { n.notify(message); }, notifier);
    }
    }
    private:
    Notifiers notifiers_;
    };
    Since all our notifier classes implement the notify function, the code will compile and run. If your
    notifier classes had different methods, you could, for instance, create a function object that has over-
    loads of operator() for different types.
    Because NotificationSystem is now a template, we have to either specify the list of types each time
    we create it or provide a type alias. You can use the final class like so:
    using MyNotificationSystem = NotificationSystem<SMSNotifier, EMailNotifier>;
    auto sn = SMSNotifier{};
    auto en = EMailNotifier{};
    auto ns = MyNotificationSystem{{sn, en}};
    ns.notify("Quinn, Wade, Arturo, Rembrandt");Importance of Software Architecture and Principles of Great Design

    This approach is guaranteed not to allocate separate memory for each notifier or use a virtual table.
    However, in some cases, this approach results in less extensibility, since once the variant is declared,
    you cannot add another type to it.
    It’s noteworthy that we used dependency injection in our examples. It is a software engi-
    neering technique to implement the dependency inversion principle. It’s about injecting
    the dependencies from the outside through constructors or setters rather than creating
    them internally, which is beneficial to code testability (think about injecting mock objects,
    for example). There are frameworks for injecting dependencies across entire applications,
    such as [Boost].DI, Google Fruit, Hypodermic, Kangaru, and Wallaroo.
 */

int main()
{
    auto notifiers = NotificationSystem::Notifiers{};
    notifiers.emplace_back(std::make_unique<SMSNotifier>());
    notifiers.emplace_back(std::make_unique<EmailNotifier>());
    auto ns = NotificationSystem{std::move(notifiers)};
    ns.notify("Quinn, Wade, Arturo, Rembrandt");
}