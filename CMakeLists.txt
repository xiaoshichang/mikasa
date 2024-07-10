cmake_minimum_required(VERSION 3.20)

project(mikasa)

include(Cmake/SetupDependencyLibrariesRoot.cmake)
include(Cmake/SetupCompiler.cmake)
include(Cmake/SetupBuildTypeDefs.cmake)
include(Cmake/SetupPlatformDefs.cmake)
include(Cmake/SetupProjectVars.cmake)
include(Cmake/SetupPythonLibrary.cmake)
include(Cmake/SetupBoostLibrary.cmake)
include(Cmake/Utils.cmake)

# include CTest in root toolchain.macos.cmake
include(CTest)

# add and build imgui
add_subdirectory(ThirdPartySource/imgui)

include_directories(Source)
add_subdirectory(Source)

add_subdirectory(Test)