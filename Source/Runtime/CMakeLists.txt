
FILE(GLOB_RECURSE EngineSrc "*.cpp" "*.mm" "*.h")

add_library(${EngineDllName} STATIC ${EngineSrc})
target_link_libraries(${EngineDllName} PUBLIC d3d12 d3dcompiler dxgi dxguid PRIVATE ${Boost_LIBRARIES})