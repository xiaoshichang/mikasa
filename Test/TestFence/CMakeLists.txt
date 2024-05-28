add_executable(Test_Fence Test_Fence.cpp)
target_link_libraries(Test_Fence ${EngineDllName})
add_test(NAME Test_Fence COMMAND Test_Fence)