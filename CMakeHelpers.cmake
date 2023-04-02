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
