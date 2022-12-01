#include "UfoLogic.h"

void UfoLogic::RegisterObject(Context* context)
{
    context->RegisterFactory<UfoLogic>();
}

UfoLogic::UfoLogic(Context* context)
    : LogicComponent(context)
    , verticalVelocity_(0.0f)
    , jumpDelay_(0.0f)
{
    SetUpdateEventMask(LogicComponentEvents::Update);
}

// В конструкторе компонент еще не прикреплен к ноде, поэтому подписываемся на события здесь
void UfoLogic::OnNodeSet(Node* node)
{
    SubscribeToEvent(node_, E_NODECOLLISIONSTART, URHO3D_HANDLER(UfoLogic, HandleCollisionStart));
    SubscribeToEvent(node_, E_NODECOLLISIONEND, URHO3D_HANDLER(UfoLogic, HandleCollisionEnd));
}

// Событие возникает при начале касания НЛО и другого физического тела
void UfoLogic::HandleCollisionStart(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollisionStart;
    Node* otherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());

    // Если НЛО касается трубы, то игра заканчивается
    if (otherNode->GetName() == "Pipe")
        GLOBAL->neededGameState_ = GS_DEAD;
}

// Событие возникает, когда НЛО перестает касаться другого физического тела
void UfoLogic::HandleCollisionEnd(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollisionEnd;
    Node* otherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());

    // Зазор между трубами тоже является физическим телом. Нам нужно увеличить игровой счет,
    // когда НЛО успешно пролетает зазор
    if (otherNode->GetName() == "Barrier")
    {
        // НЛО может покидать зазор при рестарте уровня (барьеры перемещаются в другое место)
        // или при проигрыше (НЛО, кувыркаясь, улетает за пределы экрана). Поэтому проверяем, что
        // игра находится в правильном состоянии
        if (GLOBAL->gameState_ == GS_GAMEPLAY)
            GLOBAL->SetScore(GLOBAL->GetScore() + 1);
    }
}

// Метод вызывается при рестарте игры
void UfoLogic::Reset()
{
    verticalVelocity_ = 0.0f;
    jumpDelay_ = 0.0f;
}

void UfoLogic::Update(float timeStep)
{
    // После столкновения с препятствием НЛО, кувыркаясь, улетает за пределы экрана
    if (GLOBAL->gameState_ == GS_DEAD)
    {
        // Вращаем тарелку
        node_->Rotate(Quaternion(0.0f, timeStep * 200.0f, -timeStep * 400.0f));

        // Запрещаем НЛО улетать в бесконечность
        if (node_->GetPosition().z_ > -50.0f)
        {
            // Так как НЛО вращается вокруг своей оси, то перемещаем его
            // в мировых координатах, а не в локальных
            node_->Translate(Vector3(0.0f, -10.0f * timeStep, -30.0f * timeStep), TransformSpace::World);
        }

        return;
    }

    // В игровом состоянии GS_INTRO нам не нужно производить с тарелкой никаких действий
    if (GLOBAL->gameState_ != GS_GAMEPLAY)
        return;

    Vector3 pos = node_->GetPosition();

    // Уменьшаем скорость по вертикали с учетом ускорения свободного падения
    verticalVelocity_ -= timeStep * GRAV_ACC;
    
    // Уменьшаем задержку до следующего прыжка
    if (jumpDelay_ > 0.0f)
        jumpDelay_ -= timeStep;

    // Если игрок нажал левую кнопку мыши и с момента прошлого прыжка прошло
    // достаточно времени, то задаем определённую вертикальную скорость и проигрываем звук
    if (INPUT->GetMouseButtonPress(MOUSEB_LEFT) && jumpDelay_ <= 0.0f)
    {
        verticalVelocity_ = UP_SPEED;
        SoundSource* soundSource = node_->GetOrCreateComponent<SoundSource>();
        soundSource->Play(CACHE->GetResource<Sound>("Sounds/Jump.wav"));

        // Устанавливаем задержку до следующего прыжка
        jumpDelay_ = 0.75f;
    }

    // Перемещаем НЛО по вертикали в соответствии с его скоростью
    pos += Vector3::UP * verticalVelocity_ * timeStep;
    node_->SetPosition(pos);

    // Игра заканчивается, если НЛО вылетает за пределы экрана
    AnimatedModel* animatedModel = node_->GetComponent<AnimatedModel>();
    if (!animatedModel->IsInView())
        GLOBAL->neededGameState_ = GS_DEAD;
}
