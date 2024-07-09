message(STATUS "============= Setup Python Library ============")


set(PythonLibsDir ${PYTHON_ROOT}/libs)
message(STATUS "PythonLibsDir: ${PythonLibsDir}")
set(PythonIncludeDir ${PYTHON_ROOT}/include)
message(STATUS "PythonIncludeDir: ${PythonIncludeDir}")
set(PythonCoreDll ${PYTHON_ROOT}/python312.dll)
message(STATUS "PythonCoreDll: ${PythonCoreDll}")

if (${MIKASA_TARGET_PLATFORM} STREQUAL ${TARGET_PLATFORM_Windows64})
    include_directories(${PythonIncludeDir})
    link_directories(${PythonLibsDir})
else ()
    message(FATAL_ERROR "unknown TARGET_PLATFORM")
endif ()


function(copy_python_dll some_target)
    add_custom_command(TARGET ${some_target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PythonCoreDll}" $<TARGET_FILE_DIR:${some_target}>)
endfunction()
