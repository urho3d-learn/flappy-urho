#include "EnvironmentLogic.h"

void EnvironmentLogic::RegisterObject(Context* context)
{
    context->RegisterFactory<EnvironmentLogic>();
}

EnvironmentLogic::EnvironmentLogic(Context* context)
    : LogicComponent(context)
{
    SetUpdateEventMask(LogicComponentEvents::Update);
}

// Вращаем фоновый скайбокс для создания иллюзии движения
void EnvironmentLogic::Update(float timeStep)
{
    // Если НЛО врезалось в преграду, то вращать не нужно
    if (GLOBAL->gameState_ == GS_GAMEPLAY || GLOBAL->gameState_ == GS_INTRO)
        node_->Rotate(Quaternion(0.0f, -timeStep * BAR_SPEED, 0.0f));
}
