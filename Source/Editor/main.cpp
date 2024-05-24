#include <iostream>
#include "Runtime/Foundation/Log/Logger.h"

int main()
{
    std::cout << "hello world." << std::endl;
    mikasa::Foundation::Logger::Init();
    return 0;
}