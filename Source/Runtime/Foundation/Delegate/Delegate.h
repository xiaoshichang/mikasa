#pragma once
#include "Runtime/Foundation/Foundation.h"
#include <list>
#include <functional>

namespace mikasa::Runtime::Foundation
{
    template<typename... TArgs>
    struct DelegateItem
    {
        using FuncType = std::function<void(TArgs... args)>;

        DelegateItem(void* targetObject, FuncType targetFunction)
            : TargetObject(targetObject)
            , TargetFunction(targetFunction)
        {
        }

        void operator()(TArgs... args)
        {
            TargetFunction(args...);
        }

        void* TargetObject;
        FuncType TargetFunction;
    };


    template<typename... TArgs>
    class Delegate
    {
        using FuncType = std::function<void(TArgs... args)>;

    public:
        Delegate() = default;
        ~Delegate()
        {
            Clear();
        }

        void operator+=(const DelegateItem<TArgs...>& target)
        {
            Targets_.push_back(target);
        }

        void operator-=(const DelegateItem<TArgs...>& target)
        {
            Targets_.remove_if([&] (const DelegateItem<TArgs...>& item)
            {
                if (target.TargetObject != nullptr)
                {
                    return target.TargetObject == item.TargetObject &&
                    target.TargetFunction.target_type().hash_code() == item.TargetFunction.target_type().hash_code();
                }
                else
                {
                    return target.TargetFunction.target_type().hash_code() == item.TargetFunction.target_type().hash_code();
                }
            });
        }

        void operator()(TArgs... args)
        {
            for (auto& it : Targets_)
            {
                it(args...);
            }
        }

        uint32 Count()
        {
            return Targets_.size();
        }

        static DelegateItem<TArgs...> MemberFunctionDelegate(void* object, FuncType call)
        {
            return DelegateItem(object, call);
        }

        static DelegateItem<TArgs...> StaticFunctionDelegate(FuncType call)
        {
            return DelegateItem(nullptr, call);
        }

    private:
        void Clear()
        {
            Targets_.clear();
        }

    private:
        std::list<DelegateItem<TArgs...>> Targets_;
    };

}

