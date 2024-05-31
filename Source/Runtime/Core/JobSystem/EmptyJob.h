#pragma once
#include "Job.h"

namespace mikasa::Runtime::Core
{
    class EmptyJob : public Job
    {
    public:
        explicit EmptyJob(std::string message) : Message_(std::move(message)){}
    public:
        void Execute() override;

    private:
        std::string Message_;
    };

}
