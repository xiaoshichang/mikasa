add_executable(Test_Imgui Test_Imgui.cpp)
target_link_libraries(Test_Imgui imgui d3d11)
add_test(NAME Test_Imgui COMMAND Test_Imgui)