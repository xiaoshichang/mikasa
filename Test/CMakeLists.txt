add_subdirectory(TestAutoResetEvent)
add_subdirectory(TestSemaphore)
add_subdirectory(TestCriticalSection)
add_subdirectory(TestLockFreeQueue)
add_subdirectory(TestBoostPython)
add_subdirectory(TestDelegate)

if (${MIKASA_TARGET_PLATFORM} STREQUAL ${TARGET_PLATFORM_Windows64})
    add_subdirectory(TestDX11)
    add_subdirectory(TestImgui)
endif ()

