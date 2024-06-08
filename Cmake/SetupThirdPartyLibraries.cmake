

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


