add_executable(TestDX11_Triangle TestDX11_Triangle.cpp)
set_target_properties (TestDX11_Triangle PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")
target_link_libraries(TestDX11_Triangle user32 d3d11 d3dcompiler)

add_custom_command(TARGET TestDX11_Triangle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/sample.vs
        ${CMAKE_CURRENT_BINARY_DIR}/sample.vs)
add_custom_command(TARGET TestDX11_Triangle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/sample.ps
        ${CMAKE_CURRENT_BINARY_DIR}/sample.ps)