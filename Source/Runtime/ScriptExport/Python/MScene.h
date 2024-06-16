#pragma once

#include <boost/python.hpp>
#include "Runtime/Module/SceneModule/SceneModule.h"

using namespace mikasa::Runtime::Module;
using namespace boost::python;


auto LogCurrentScene()
{
    if (SceneModule::Current == nullptr)
    {
        Logger::Warning("Current Scene is nullptr");
        return;
    }
    SceneModule::Current->LogTotalSceneInfo();
}

BOOST_PYTHON_MODULE(MScene)
{
    def("LogCurrentScene", LogCurrentScene);
}
