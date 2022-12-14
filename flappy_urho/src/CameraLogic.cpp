#include "CameraLogic.h"

void CameraLogic::RegisterObject(Context* context)
{
    context->RegisterFactory<CameraLogic>();
}

CameraLogic::CameraLogic(Context* context)
    : LogicComponent(context)
{
    SetUpdateEventMask(LogicComponentEvents::Update);
}

// В целях отладки камеру можно приближать и удалять
void CameraLogic::Update(float timeStep)
{
    // При вращении колеса мыши двигаем камеру
    int wheel = INPUT->GetMouseMoveWheel();
    if (wheel != 0)
    {
        Vector3 pos = node_->GetPosition();
        pos.z_ += wheel * 4.0f;

        // Ограничиваем максимальное приближение
        if (pos.z_ > -5.0f)
            pos.z_ = -5.0f;
        
        node_->SetPosition(pos);
    }

    // При нажатии правой кнопки мыши камера возвращается в стандартное положение
    if (INPUT->GetMouseButtonPress(MOUSEB_RIGHT))
        node_->SetPosition(CAMERA_DEFAULT_POS);
}
