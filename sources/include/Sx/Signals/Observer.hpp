#pragma once

#include <list>
#include <map>

namespace Sx::Signals
{
    class Connection;
    class SignalBase;

    class Observer
    {
    public:
        Observer() = default;
        Observer(const Observer&) noexcept;

        ~Observer() noexcept;

        Observer& operator=(const Observer&) noexcept;

    private:
        friend class Connection;

        static Observer* global();

        void attach(Connection* c);
        void detach(Connection* c);

        std::list<Connection*> connections;
    };

};  // namespace Sx::Signals
