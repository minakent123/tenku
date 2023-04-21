function(print_all_variables)
    get_cmake_property(VARS VARIABLES)
    foreach(VAR ${VARS})
        message(STATUS "${VAR}=${${VAR}}")
    endforeach()
endfunction()

macro(run_code_format TARGET)
    if(MSVC)
        add_custom_command(
            TARGET ${TARGET}
            PRE_BUILD
            COMMAND ${CMAKE_SOURCE_DIR}/scripts/code_format.bat
            COMMENT "run code_format.bat"
        )
        endif()
endmacro()

macro(set_common_variables)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        set(LIB_BUILD_TYPE debug)
        set(LIB_SUFFIX "d")
    else()
        set(LIB_BUILD_TYPE release)
    endif()
endmacro()
