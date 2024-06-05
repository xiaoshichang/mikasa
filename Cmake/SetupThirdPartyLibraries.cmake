

message(STATUS "============= Setup ThirdParty Libraries ============")

##########################################
####        setup boost library        ###
##########################################
set(BOOST_ROOT ${ThirdPartyLibraryRoot}/boost_1_80_0/Installed)

find_package(Boost COMPONENTS log program_options python REQUIRED)
message(STATUS "BOOST_ROOT: ${BOOST_ROOT}")
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

# https://stackoverflow.com/questions/35367469/force-cmake-visualstudio-to-use-static-libs-of-boost-python
add_definitions(-DBOOST_PYTHON_STATIC_LIB)

# setup python
set(PythonHome ${ThirdPartySourceRoot}/python/Python-3.12.3)
include_directories(${ThirdPartySourceRoot}/python/Python-3.12.3/Include)

if (${MIKASA_TARGET_PLATFORM} STREQUAL ${TARGET_PLATFORM_Windows64})
    include_directories(${ThirdPartySourceRoot}/python/Python-3.12.3/PC)
    link_directories(${ThirdPartySourceRoot}/python/Python-3.12.3/PCbuild/amd64)
    set(PythonCoreDll ${ThirdPartySourceRoot}/python/Python-3.12.3/PCbuild/amd64/python312.dll)
    message(STATUS "PythonCoreDll: ${PythonCoreDll}")
else ()
    message(FATAL_ERROR "unknown TARGET_PLATFORM")
endif ()

function(copy_python_dll some_target)
    add_custom_command(TARGET ${some_target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different # which executes "cmake - E copy_if_different..."
        "${PythonCoreDll}"
        $<TARGET_FILE_DIR:${some_target}>)
endfunction()

