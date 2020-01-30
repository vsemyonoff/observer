#pragma once

#include <Sx/Signals/Connection.hpp>

#include <utility>

namespace Sx::Signals {

template <typename T> struct Function;
template <typename ReturnType, typename... Args>
struct Function<ReturnType(Args ...)> final
{
    using ProxyCall = ReturnType (*)(Observer*, Args ...);

    ProxyCall const function;
    Observer* const instance;

    // Member function
    template <auto function, typename T>
    static inline Function bind(T* instance) {
        return {
            [] (Observer* instance, Args ... args) {
                return (static_cast<T *>(instance)->*function)(args ...);
            },
            instance
        };
    }

    // Callable
    template <typename T>
    static inline Function bind(T* instance) {
        return {
            [] (Observer* instance, Args ... args) {
                return static_cast<T*>(instance)->operator()(args ...);
            },
            instance,
        };
    }

    // Free function
    template <auto function>
    static inline Function bind() {
        return {
            [] (Observer* /* null */, Args ... args) {
                return (*function)(args ...);
            }
        };
    }

    static inline Function fromConnection(Connection* c) {
        return {
            reinterpret_cast<ProxyCall>(c->function),
            c->instance
        };
    }

    inline operator Connection() const {
        return {
            reinterpret_cast<Pointer>(function),
            instance
        };
    }

    template <typename... Uref>
    inline ReturnType operator()(Uref&& ... args) {
        return (*function)(instance, std::forward<Uref>(args) ...);
    }
};

}; // namespace Sx::Signals
