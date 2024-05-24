
FILE(GLOB_RECURSE ExeSrc "*.cpp" "*.mm" "*.h")

add_executable(${PlayerExeName} ${ExeSrc})
target_link_libraries(${PlayerExeName} ${EngineDllName})