macro(add_assets_directory target directory)
    add_custom_command(
            TARGET ${target} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/${directory}
                $<TARGET_FILE_DIR:${target}>/${directory}
    )
endmacro()