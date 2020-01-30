project ("CommonTest")

set (SOURCE_FILES "add.cpp"
                  "edit.cpp"
                  "list.cpp"
                  "remove.cpp"
    )

add_boost_test("${PROJECT_NAME}" "${SOURCE_FILES}" Sx::observer::${LIB_TYPE})
