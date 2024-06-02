
FILE(GLOB_RECURSE ExeSrc "*.cpp" "*.mm" "*.h")

add_executable(${PlayerExeName} ${ExeSrc})
target_link_libraries(${PlayerExeName} ${EngineDllName})
set_target_properties(${PlayerExeName}	PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")