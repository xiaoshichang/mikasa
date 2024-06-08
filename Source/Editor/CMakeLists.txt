
FILE(GLOB_RECURSE ExeSrc "*.cpp" "*.mm" "*.h")

add_executable(${EditorExeName} ${ExeSrc})
target_link_libraries(${EditorExeName} ${EngineDllName})
copy_python_dll(${EditorExeName})
set_target_properties(${EditorExeName}	PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")