
message(STATUS "=============== Setup Project Vars ===================")

set(ThirdPartySourceRoot ${CMAKE_SOURCE_DIR}/ThirdPartySource)
message(STATUS "ThirdPartySourceRoot: ${ThirdPartySourceRoot}")

set(ThirdPartyLibraryRoot ${CMAKE_SOURCE_DIR}/ThirdPartyLibrary)
message(STATUS "ThirdPartyLibraryRoot: ${ThirdPartyLibraryRoot}")

set(ThirdPartySupportRoot ${CMAKE_SOURCE_DIR}/ThirdPartySupport)
message(STATUS "ThirdPartySupportRoot: ${ThirdPartySupportRoot}")

set(EngineDllName MikasaEngine.${MIKASA_TARGET_PLATFORM})
message(STATUS "EngineDllName: ${EngineDllName}")

set(PlayerExeName MikasaPlayer.${MIKASA_TARGET_PLATFORM})
message(STATUS "PlayerExeName: ${PlayerExeName}")

set(EditorExeName MikasaEditor.${MIKASA_TARGET_PLATFORM})
message(STATUS "EditorExeName: ${EditorExeName}")