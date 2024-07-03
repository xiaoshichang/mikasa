function(copy_asset_dir some_target)
    add_custom_command(TARGET ${some_target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Asset" $<TARGET_FILE_DIR:${some_target}>/Asset)
endfunction()