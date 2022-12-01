#pragma once
#include "Global.h"

// Этот компонент прикрепляется к ноде со скайбоксом
class EnvironmentLogic : public LogicComponent
{
    URHO3D_OBJECT(EnvironmentLogic, LogicComponent);

public:
    static void RegisterObject(Context* context);

    EnvironmentLogic(Context* context);
    void Update(float timeStep);
};
