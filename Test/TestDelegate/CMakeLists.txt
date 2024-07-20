add_executable(Test_Delegate Test_Delegate.cpp)
target_link_libraries(Test_Delegate ${EngineDllName})
add_test(NAME Test_Delegate COMMAND Test_Delegate)