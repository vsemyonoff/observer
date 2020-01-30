#pragma once

#include <Sx/Signals/Combiner.hpp>
#include <Sx/Signals/Function.hpp>
#include <Sx/Signals/Observer.hpp>
#include <Sx/Signals/SignalBase.hpp>

namespace Sx::Signals {

template <typename T, template<typename> typename C = LastValue> class Signal;
template <typename R, template<typename> typename C, typename... Args>
class Signal<R(Args...), C> final : protected SignalBase, public Observer {
  public:
    using ReturnType   = R;
    using Combiner     = C<R>;
    using Signature    = ReturnType(Args...);
    using Callback     = Function<Signature>;

    // Member function
    template <auto function, typename T>
    Connection* connect(T* instance) {
        static_assert(std::is_base_of<Observer, T>::value,
                      "T must be derived from Observer");

        ScopedConnection c = std::make_unique<Connection>(
            Callback::template bind<function>(instance));
        Connection* ptr = c.get();
        insert(std::move(c));

        return ptr;
    }

    template <auto function, typename T>
    Connection* connect(T& instance) {
        return connect<function>(std::addressof(instance));
    }

    // Callable objects
    template <typename T>
    Connection* connect(T* instance) {
        static_assert(std::is_base_of<Observer, T>::value,
                      "T must be derived from Observer");

        ScopedConnection c = std::make_unique<Connection>(
            Callback::template bind(instance));
        Connection* ptr = c.get();
        insert(std::move(c));

        return ptr;
    }

    template <typename T>
    Connection* connect(T& instance) {
        return connect(std::addressof(instance));
    }

    // Free && static member function
    template <auto function>
    Connection* connect() {
        ScopedConnection c = std::make_unique<Connection>(
            Callback::template bind<function>());
        Connection* ptr = c.get();
        insert(std::move(c));

        return ptr;
    }

    // Call operator
    template <typename... Uref>
    typename Combiner::ResultType operator()(Uref&& ... args) {
        Combiner combiner;

        emitting = true;
        for (auto i = slots.begin(), end = slots.end(); i != end; ) {
            // Remove detached connection
            if (i->get()->detached) {
                i = remove(i);
                continue;
            }

            Connection* connection = i++->get();

            // Skip disabled connections
            if (connection->disabled) {
                continue;
            }

            Callback callback = Callback::fromConnection(connection);

            // Exec callback
            if constexpr (std::is_same<void, ReturnType>::value) {
                callback(std::forward<Uref>(args) ...);
            } else {
                if (!combiner(callback(std::forward<Uref>(args) ...)))
                    break;
            }
        }
        emitting = false;

        return combiner.result();
    }
};

}; // namespace Sx::Signals
