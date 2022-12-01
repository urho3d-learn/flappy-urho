#pragma once
#include "Global.h"

// Этот компонент прикрепляется к ноде с камерой
class CameraLogic : public LogicComponent
{
    URHO3D_OBJECT(CameraLogic, LogicComponent);

public:
    static void RegisterObject(Context* context);

    CameraLogic(Context* context);
    void Update(float timeStep);
};
