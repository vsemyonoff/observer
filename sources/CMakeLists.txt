project ("Observer" VERSION "1.0.0")

set (HEADER_FILES "include/Sx/Signals/Combiner.hpp"
                 "include/Sx/Signals/Connection.hpp"
                 "include/Sx/Signals/Function.hpp"
                 "include/Sx/Signals/Observer.hpp"
                 "include/Sx/Signals/Signal.hpp"
                 "include/Sx/Signals/SignalBase.hpp"
                 "include/Sx/Types.hpp"
                 )

set (SOURCE_FILES "src/Sx/Signals/Connection.cpp"
                 "src/Sx/Signals/Observer.cpp"
                 "src/Sx/Signals/SignalBase.cpp"
                 )

add_custom_library ("${PROJECT_NAME}" "${HEADER_FILES};${SOURCE_FILES}" "include" "" "src")
