#include "BarrierLogic.h"

void BarrierLogic::RegisterObject(Context* context)
{
    context->RegisterFactory<BarrierLogic>();
}

BarrierLogic::BarrierLogic(Context* context)
    :  LogicComponent(context)
{
    SetUpdateEventMask(LogicComponentEvents::Update);
}

// НЛО всегда находится в нуле по горизонтали, а барьеры движутся мимо него.
// Это создает иллюзию движения и не позволяет НЛО улетать в бесконечность
void BarrierLogic::Update(float timeStep)
{
    // Не двигаем барьер, если НЛО врезался в преграду или игра еще не началась
    // (в режиме заставки все барьеры находятся за границей экрана)
    if (GLOBAL->gameState_ != GS_GAMEPLAY)
        return;

    // Двигаем барьер влево
    Vector3 pos = node_->GetPosition();
    pos += Vector3::LEFT * timeStep * BAR_SPEED;

    // Если барьер уходит далеко влево, то перемещаем его в правый конец очереди
    // и меняем его координату по высоте
    if (pos.x_ < -BAR_OUTSIDE_X)
    {
        pos.x_ += NUM_BARRIERS * BAR_INTERVAL;
        pos.y_ = BAR_RANDOM_Y;
    }

    node_->SetPosition(pos);
}
