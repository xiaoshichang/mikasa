#pragma once
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include <string>
#include <vector>

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Module
{
    struct VideoAdapterInfo
    {
        std::string Message;
        uint64 DedicatedVideoMemory;
        uint64 DedicatedSystemMemory;
        uint64 SharedSystemMemory;
    };

    class SystemInfoModule
    {
    public:
        static void Init(const ApplicationInitParam& info);
        static void Uninit();
        static void OutputInfo()
        {
            Logger::Info("-------------- System Information ---------------");
            Logger::Info("NumOfProcessors : %lld", NumOfProcessors_);
            Logger::Info("AvailVirtualMemory : %llu B, %llu GB", AvailVirtualMemoryInByte_, AvailVirtualMemoryInByte_ / BYTES_PER_GB );
            Logger::Info("TotalVirtualMemory : %llu B, %llu GB", TotalVirtualMemoryInByte_, TotalVirtualMemoryInByte_ / BYTES_PER_GB);
            Logger::Info("AvailPhysicsMemory : %llu B, %llu GB", AvailPhysicsMemoryInByte_, AvailPhysicsMemoryInByte_ / BYTES_PER_GB);
            Logger::Info("TotalPhysicsMemory : %llu B, %llu GB", TotalPhysicsMemoryInByte_, TotalPhysicsMemoryInByte_ / BYTES_PER_GB);
            Logger::Info("OsAllocationGranularity : %llu B, %llu KB", OsAllocationGranularity_, OsAllocationGranularity_ / BYTES_PER_KB);
            OutputVideoAdapterInfos();
            Logger::Info("-------------------------------------------------");
        }

    private:
        static void InitAllVideoAdapterInfos();
        static void OutputVideoAdapterInfos();


    private:
        static uint64 NumOfProcessors_;
        static uint64 AvailVirtualMemoryInByte_;
        static uint64 TotalVirtualMemoryInByte_;
        static uint64 AvailPhysicsMemoryInByte_;
        static uint64 TotalPhysicsMemoryInByte_;
        static uint64 OsAllocationGranularity_;
        static std::vector<VideoAdapterInfo> VideoAdapterInfos_;

        static const uint64 BYTES_PER_KB = 1024;
        static const uint64 BYTES_PER_MB = 1024 * 1024;
        static const uint64 BYTES_PER_GB = 1024 * 1024 * 1024;
    };
}




