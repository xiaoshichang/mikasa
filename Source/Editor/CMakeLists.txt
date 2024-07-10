
FILE(GLOB_RECURSE ExeSrc "*.cpp" "*.mm" "*.h")

add_executable(${EditorExeName} ${ExeSrc})
target_link_libraries(${EditorExeName} ${EngineDllName} imgui)
copy_python_dll(${EditorExeName})
copy_asset_dir(${EditorExeName})
set_target_properties(${EditorExeName}	PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")