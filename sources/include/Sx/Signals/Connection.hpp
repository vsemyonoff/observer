#pragma once

#include <Sx/Types.hpp>

namespace Sx::Signals {

class Observer;
class SignalBase;

struct Connection final {
    Connection() =                   delete;
    Connection(Pointer, Observer*) noexcept;
    ~Connection()                  noexcept;
    void disconnect()              noexcept;

    Pointer     const function             ;
    Observer*   const instance             ;
    SignalBase*         signal =    nullptr;
    bool              disabled =      false;
    bool              detached =      false;
};

}; // namespace Sx::Signals
