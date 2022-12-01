#pragma once
#include "Global.h"

// Этот компонент прикрепляется к нодам с барьерами.
// Барьер содержит две дочерние ноды - верхнюю и нижнюю трубы
class BarrierLogic : public LogicComponent
{
    URHO3D_OBJECT(BarrierLogic, LogicComponent);

public:
    static void RegisterObject(Context* context);

    BarrierLogic(Context* context);
    void Update(float timeStep);
};
