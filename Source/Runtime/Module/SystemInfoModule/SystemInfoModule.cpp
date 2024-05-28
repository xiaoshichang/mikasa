#ifdef MIKASA_TARGET_PLATFORM_Window

#include "SystemInfoModule.h"
#include <windows.h>
#include <dxgi.h>

using namespace mikasa::Runtime::Module;

uint64 SystemInfoModule::NumOfProcessors_ = 0;
uint64 SystemInfoModule::AvailVirtualMemoryInByte_ = 0;
uint64 SystemInfoModule::TotalVirtualMemoryInByte_ = 0;
uint64 SystemInfoModule::AvailPhysicsMemoryInByte_ = 0;
uint64 SystemInfoModule::TotalPhysicsMemoryInByte_ = 0;
uint64 SystemInfoModule::OsAllocationGranularity_ = 0;
std::vector<VideoAdapterInfo> SystemInfoModule::VideoAdapterInfos_;

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

    InitAllVideoAdapterInfos();
}

void SystemInfoModule::Uninit()
{

}

void SystemInfoModule::InitAllVideoAdapterInfos()
{
    IDXGIAdapter* pAdapter;
    std::vector <IDXGIAdapter*> vAdapters;
    IDXGIFactory* pFactory = nullptr;
    DXGI_ADAPTER_DESC desc;
    // Create a DXGIFactory object.
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory)))
    {
        throw;
    }
    for (UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
    {
        if (pAdapter->GetDesc(&desc) != S_OK)
        {
            throw;
        }
        vAdapters.push_back(pAdapter);
    }
    pFactory->Release();

    char message[256];
    for (auto adapter: vAdapters)
    {
        if (adapter->GetDesc(&desc) != S_OK)
        {
            throw;
        }
        VideoAdapterInfo info;
        wcstombs(message, desc.Description, 128);
        info.Message = std::string(message);
        info.DedicatedSystemMemory = desc.DedicatedSystemMemory;
        info.DedicatedVideoMemory = desc.DedicatedVideoMemory;
        info.SharedSystemMemory = desc.SharedSystemMemory;
        VideoAdapterInfos_.push_back(info);
    }
}

void SystemInfoModule::OutputVideoAdapterInfos()
{
    Logger::Info("%d video adapters found.", VideoAdapterInfos_.size());
    for(auto& info : VideoAdapterInfos_)
    {
        Logger::Info("\t Desc: %s" , info.Message.c_str());
        Logger::Info("\t DedicatedSystemMemory:%.2f GB", info.DedicatedSystemMemory / (float)BYTES_PER_GB);
        Logger::Info("\t DedicatedVideoMemory:%.2f GB", info.DedicatedVideoMemory / (float)BYTES_PER_GB);
        Logger::Info("\t SharedSystemMemory:%.2f GB", info.SharedSystemMemory / (float)BYTES_PER_GB);
        Logger::Info("\t --------------------------");
    }
}


#endif