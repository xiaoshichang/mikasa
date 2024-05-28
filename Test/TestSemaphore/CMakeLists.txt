add_executable(Test_Semaphore Test_Semaphore.cpp)
target_link_libraries(Test_Semaphore ${EngineDllName})
add_test(NAME Test_Semaphore COMMAND Test_Semaphore)