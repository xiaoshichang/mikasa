message(STATUS "============= Setup Platform Definitions ============")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_compile_definitions("MIKASA_PLATFORM_64bit")
    message(STATUS "MIKASA_PLATFORM_64bit")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    add_compile_definitions("MIKASA_PLATFORM_32bit")
    message(STATUS "MIKASA_PLATFORM_32bit")
else()
    message(FATAL_ERROR  "-- unsupported platform: ${CMAKE_SIZEOF_VOID_P}")
endif()


# check CMAKE_SYSTEM_NAME
message(STATUS "CMAKE_SYSTEM_NAME : ${CMAKE_SYSTEM_NAME}")


# check if MIKASA_TARGET_PLATFORM is defined?
if (NOT DEFINED MIKASA_TARGET_PLATFORM)
    message(FATAL_ERROR "MIKASA_TARGET_PLATFORM is not defined.")
ENDIF ()
message(STATUS "MIKASA_TARGET_PLATFORM : ${MIKASA_TARGET_PLATFORM}")


set(TARGET_PLATFORM_Windows64 "Windows64")
set(TARGET_PLATFORM_Macos "Macos")
if (${MIKASA_TARGET_PLATFORM} STREQUAL ${TARGET_PLATFORM_Windows64})
    add_compile_options("/utf-8")

elseif (${MIKASA_TARGET_PLATFORM} STREQUAL ${TARGET_PLATFORM_Macos})
    set(CMAKE_MACOSX_RPATH 1)

else ()
    message(FATAL_ERROR "unknown TARGET_PLATFORM")
endif ()
