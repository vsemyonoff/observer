project ("ObserverTest")

set (SOURCE_FILES "CombinerTest.cpp")

add_boost_test("${PROJECT_NAME}" "${SOURCE_FILES}" Sx::observer)
