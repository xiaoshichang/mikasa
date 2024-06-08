cmake_minimum_required(VERSION 3.20)

project(mikasa)

include(Cmake/SetupCompiler.cmake)
include(Cmake/SetupBuildTypeDefs.cmake)
include(Cmake/SetupPlatformDefs.cmake)
include(Cmake/SetupProjectVars.cmake)
include(Cmake/SetupPythonLibrary.cmake)
include(Cmake/SetupThirdPartyLibraries.cmake)

# include CTest in root toolchain.macos.cmake
include(CTest)

include_directories(Source)
add_subdirectory(Source)

add_subdirectory(Test)