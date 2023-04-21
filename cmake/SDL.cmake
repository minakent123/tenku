function(set_sdl_properties TARGET)
    target_include_directories(${TARGET} PRIVATE
        ${CMAKE_SOURCE_DIR}/library/sdl/include
    )
    target_link_directories(${TARGET} PRIVATE
        ${CMAKE_SOURCE_DIR}/library/sdl/lib/${LIB_BUILD_TYPE}
    )
    target_link_libraries(${TARGET} PRIVATE
        SDL2-static${LIB_SUFFIX}
        Imm32
        Setupapi
        Version
        Winmm
    )
endfunction()
