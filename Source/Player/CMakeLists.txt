
FILE(GLOB_RECURSE ExeSrc "*.cpp" "*.mm" "*.h")

add_executable(${PlayerExeName} ${ExeSrc})
target_link_libraries(${PlayerExeName} ${EngineDllName})
copy_python_dll(${PlayerExeName})
copy_asset_dir(${PlayerExeName})
set_target_properties(${PlayerExeName}	PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

