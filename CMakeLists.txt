cmake_minimum_required(VERSION 3.20)

project(mikasa)

include(Cmake/SetupBuildTypeDefs.cmake)
include(Cmake/SetupPlatformDefs.cmake)
include(Cmake/SetupProjectVars.cmake)
include(Cmake/SetupThirdPartyLibraries.cmake)

include_directories(Source)
add_subdirectory(Source)