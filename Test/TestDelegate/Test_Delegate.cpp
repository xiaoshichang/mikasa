
#include "Runtime/Foundation/Delegate/Delegate.h"
#include <iostream>
#include <functional>

void GlobalOnChange(float x, float y)
{
    std::cout << "GlobalOnChange:" << x << "," << y << std::endl;
}

struct Object
{
    explicit Object(const std::string& name)
    {
        Name = name;
    }

    void OnChange(float x, float y) const
    {
        std::cout << "Object.OnChange " << Name << " " << x << "," << y << std::endl;
    }

    std::string Name;
};

int main()
{
    typedef mikasa::Runtime::Foundation::Delegate<float, float> OnPositionChangeDelegate;
    OnPositionChangeDelegate OnPositionChange;
    Object obj1("obj1");
    Object obj2("obj2");

    OnPositionChange += OnPositionChangeDelegate::StaticFunctionDelegate(GlobalOnChange);
    OnPositionChange += OnPositionChangeDelegate::MemberFunctionDelegate(&obj1, std::bind(&Object::OnChange, &obj1, std::placeholders::_1, std::placeholders::_2));
    OnPositionChange += OnPositionChangeDelegate::MemberFunctionDelegate(&obj2, std::bind(&Object::OnChange, &obj2, std::placeholders::_1, std::placeholders::_2));
    OnPositionChange(1, 1);

    OnPositionChange -= OnPositionChangeDelegate::StaticFunctionDelegate(GlobalOnChange);
    OnPositionChange(2, 2);

    OnPositionChange -= OnPositionChangeDelegate::MemberFunctionDelegate(&obj1, std::bind(&Object::OnChange, &obj1, std::placeholders::_1, std::placeholders::_2));
    OnPositionChange(3, 3);

    OnPositionChange -= OnPositionChangeDelegate::MemberFunctionDelegate(&obj2, std::bind(&Object::OnChange, &obj1, std::placeholders::_1, std::placeholders::_2));
    OnPositionChange(4, 4);

    std::cout << "count: " << OnPositionChange.Count() << std::endl;

}