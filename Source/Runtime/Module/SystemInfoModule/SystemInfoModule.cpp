
#include "SystemInfoModule.h"

#ifdef MIKASA_TARGET_PLATFORM_Window
#include <windows.h>
#endif

using namespace mikasa::Runtime::Module;

uint64 SystemInfoModule::NumOfProcessors_ = 0;
uint64 SystemInfoModule::AvailVirtualMemoryInByte_ = 0;
uint64 SystemInfoModule::TotalVirtualMemoryInByte_ = 0;
uint64 SystemInfoModule::AvailPhysicsMemoryInByte_ = 0;
uint64 SystemInfoModule::TotalPhysicsMemoryInByte_ = 0;
uint64 SystemInfoModule::OsAllocationGranularity_ = 0;

void SystemInfoModule::Init(const ApplicationInitParam& info)
{
    {
        SYSTEM_INFO sysinfo = { 0 };
        GetSystemInfo(&sysinfo);
        NumOfProcessors_ = sysinfo.dwNumberOfProcessors;
        OsAllocationGranularity_ = sysinfo.dwAllocationGranularity;
    }

    {
        MEMORYSTATUSEX meminfo = { 0 };
        meminfo.dwLength = sizeof(MEMORYSTATUSEX);
        auto ret = GlobalMemoryStatusEx(&meminfo);
        MIKASA_ASSERT(ret != 0);
        AvailVirtualMemoryInByte_ = meminfo.ullAvailVirtual;
        TotalVirtualMemoryInByte_ = meminfo.ullTotalVirtual;
        AvailPhysicsMemoryInByte_ = meminfo.ullAvailPhys;
        TotalPhysicsMemoryInByte_ = meminfo.ullTotalPhys;
    }
}

void SystemInfoModule::Uninit()
{

}
