message(STATUS "============= Setup Python Library ============")

# setup python
set(PythonHome ${ThirdPartySourceRoot}/python/Python-3.12.3)
include_directories(${ThirdPartySourceRoot}/python/Python-3.12.3/Include)

if (${MIKASA_TARGET_PLATFORM} STREQUAL ${TARGET_PLATFORM_Windows64})
    include_directories(${ThirdPartySourceRoot}/python/Python-3.12.3/PC)
    link_directories(${ThirdPartySourceRoot}/python/Python-3.12.3/PCbuild/amd64)

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(PythonCoreDll ${ThirdPartySourceRoot}/python/Python-3.12.3/PCbuild/amd64/python312.dll)
        set(PythonCoreExp ${ThirdPartySourceRoot}/python/Python-3.12.3/PCbuild/amd64/python312.exp)
        set(PythonCorePdb ${ThirdPartySourceRoot}/python/Python-3.12.3/PCbuild/amd64/python312.pdb)
        message(STATUS "PythonCoreDll: ${PythonCoreDll}")
        message(STATUS "PythonCoreExp: ${PythonCoreExp}")
        message(STATUS "PythonCorePdb: ${PythonCorePdb}")
    else ()
        set(PythonCoreDll ${ThirdPartySourceRoot}/python/Python-3.12.3/PCbuild/amd64/python312.dll)
        message(STATUS "PythonCoreDll: ${PythonCoreDll}")
    endif ()

else ()
    message(FATAL_ERROR "unknown TARGET_PLATFORM")
endif ()


function(copy_python_dll some_target)
    add_custom_command(TARGET ${some_target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PythonCoreDll}" $<TARGET_FILE_DIR:${some_target}>)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_custom_command(TARGET ${some_target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PythonCoreExp}" $<TARGET_FILE_DIR:${some_target}>)
        add_custom_command(TARGET ${some_target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PythonCorePdb}" $<TARGET_FILE_DIR:${some_target}>)
    endif ()
endfunction()
