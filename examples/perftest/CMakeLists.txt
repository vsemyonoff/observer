project ("perftest")

add_application ("${PROJECT_NAME}" "${PROJECT_NAME}.cpp" Sx::observer::${LIB_TYPE})

if (INSTALL_EXAMPLES)
    install (TARGETS "${PROJECT_NAME}" RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endif ()
