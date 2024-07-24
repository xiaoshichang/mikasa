#pragma once

#include "Runtime/Core/Scene/Transform.h"

namespace mikasa::Runtime::Core
{
    /**
 * including all transform update info from main thread.
 * use these info to update render proxy.
 */

    class StaticMeshRenderProxy;
    struct RenderProxyTransformUpdateInfo
    {
        std::shared_ptr<StaticMeshRenderProxy> Proxy = nullptr;
        Transform UpdatedTransform;
    };
}

