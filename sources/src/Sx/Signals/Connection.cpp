#include <Sx/Signals/Connection.hpp>
#include <Sx/Signals/Observer.hpp>

using namespace Sx::Signals;

Connection::Connection(Pointer f, Observer *i = nullptr) noexcept
        : function{f}, instance{i ? i : Observer::global()} {
    instance->attach(this);
}

Connection::~Connection() noexcept {
    disconnect();
}

void Connection::disconnect() noexcept {
    if (!detached) {
        instance->detach(this);
        detached = true;
    }
}
