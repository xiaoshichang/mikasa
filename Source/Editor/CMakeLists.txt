
FILE(GLOB_RECURSE ExeSrc "*.cpp" "*.mm" "*.h")

add_executable(${EditorExeName} ${ExeSrc})
target_link_libraries(${EditorExeName} ${EngineDllName})