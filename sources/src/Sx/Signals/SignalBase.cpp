#include <Sx/Signals/Connection.hpp>
#include <Sx/Signals/SignalBase.hpp>

#include <utility>

using namespace Sx::Signals;

SignalBase::SignalBase() {}

SignalBase::SignalBase(const SignalBase& other)
{
    operator=(other);
}

SignalBase& SignalBase::operator=(const SignalBase& other)
{
    for (const auto& c : other.slots)
    {
        if (!c->detached)
        {
            ScopedConnection sc = std::make_unique<Connection>(*c);
            sc->signal          = this;
            insert(std::move(sc));
        }
    }

    return *this;
}

void SignalBase::disconnect(Connection* c)
{
    c->disconnect();
    if (!emitting)
    {
        slots.remove_if([c](const ScopedConnection& co) {
            return c == co.get();
        });
    }
}

void SignalBase::insert(ScopedConnection&& c)
{
    c->signal = this;
    slots.push_back(std::move(c));
}

SignalBase::Connections::iterator SignalBase::remove(Connections::iterator pos)
{
    return slots.erase(pos);
}
