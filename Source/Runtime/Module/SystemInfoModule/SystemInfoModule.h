#pragma once
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Core/Misc/ApplicationInitParam.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

namespace mikasa
{
    namespace Runtime
    {
        namespace Module
        {
            class SystemInfoModule
            {
            public:
                static void Init(const ApplicationInitParam& info);
                static void Uninit();
                static void OutputInfo()
                {
                    Logger::Info("-------------- System Information ---------------");
                    Logger::Info("NumOfProcessors : %lld", NumOfProcessors_);
                    Logger::Info("AvailVirtualMemory : %llu B, %llu GB", AvailVirtualMemoryInByte_, AvailVirtualMemoryInByte_ );
                    Logger::Info("TotalVirtualMemory : %llu B, %llu GB", TotalVirtualMemoryInByte_, TotalVirtualMemoryInByte_ );
                    Logger::Info("AvailPhysicsMemory : %llu B, %llu GB", AvailPhysicsMemoryInByte_, AvailPhysicsMemoryInByte_ );
                    Logger::Info("TotalPhysicsMemory : %llu B, %llu GB", TotalPhysicsMemoryInByte_, TotalPhysicsMemoryInByte_ );
                    Logger::Info("OsAllocationGranularity : %llu B, %llu KB", OsAllocationGranularity_, OsAllocationGranularity_ );
                    Logger::Info("-------------------------------------------------");
                }

            private:
                static uint64 NumOfProcessors_;
                static uint64 AvailVirtualMemoryInByte_;
                static uint64 TotalVirtualMemoryInByte_;
                static uint64 AvailPhysicsMemoryInByte_;
                static uint64 TotalPhysicsMemoryInByte_;
                static uint64 OsAllocationGranularity_;


            };
        }
    }
}


