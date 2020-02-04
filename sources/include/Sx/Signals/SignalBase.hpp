#pragma once

#include <list>
#include <map>
#include <memory>

namespace Sx::Signals
{
    class Connection;
    class Observer;

    class SignalBase
    {
    public:
        SignalBase();
        SignalBase(const SignalBase& o);
        SignalBase& operator=(const SignalBase& o);

        void disconnect(Connection* c);

    protected:
        using ScopedConnection = std::unique_ptr<Connection>;
        using Connections      = std::list<ScopedConnection>;

        Connections::iterator remove(Connections::iterator c);
        void                  insert(ScopedConnection&& c);

        bool        emitting = false;
        Connections slots;
    };

};  // namespace Sx::Signals
