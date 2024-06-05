add_executable(Test_BoostPython Test_BoostPython.cpp)
target_link_libraries(Test_BoostPython PRIVATE ${Boost_LIBRARIES})

copy_python_dll(Test_BoostPython)

add_test(NAME Test_BoostPython COMMAND Test_BoostPython)