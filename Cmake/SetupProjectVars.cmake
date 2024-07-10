
message(STATUS "=============== Setup Project Vars ===================")

set(ThirdPartySourceRoot ${CMAKE_SOURCE_DIR}/ThirdPartySource)
message(STATUS "ThirdPartySourceRoot: ${ThirdPartySourceRoot}")

set(EngineDllName MikasaEngine.${MIKASA_TARGET_PLATFORM})
message(STATUS "EngineDllName: ${EngineDllName}")

set(PlayerExeName MikasaPlayer.${MIKASA_TARGET_PLATFORM})
message(STATUS "PlayerExeName: ${PlayerExeName}")

set(EditorExeName MikasaEditor.${MIKASA_TARGET_PLATFORM})
message(STATUS "EditorExeName: ${EditorExeName}")