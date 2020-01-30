project ("PerfTest")

set (LIBS Sx::observer::${LIB_TYPE} Boost::boost)
add_application ("${PROJECT_NAME}" "${PROJECT_NAME}.cpp" "${LIBS}")

if (INSTALL_EXAMPLES)
    install (TARGETS "${PROJECT_NAME}" RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endif ()
