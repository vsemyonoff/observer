#include <Sx/Signals/Connection.hpp>
#include <Sx/Signals/Observer.hpp>

using namespace Sx::Signals;

Observer::~Observer() noexcept {
    for (const auto& c : connections)
        c->detached = true;
    connections.clear();
}

Observer::Observer(const Observer&) noexcept {
}

Observer& Observer::operator=(const Observer&) noexcept {
    return *this;
}

// Static instance will hold static and free functions connections
Observer* Observer::global() {
    static Observer d;
    return &d;
}

void Observer::attach(Connection* c) {
    connections.push_back(c);
}

void Observer::detach(Connection* c) {
    connections.remove_if(
        [c] (Connection* co) {
            return c == co;
        });
}
