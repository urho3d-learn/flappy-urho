#include "Global.h"

Global::Global(Context* context)
    : Object(context)
    , score_(0)
    , scoreTextDirty_(true)
    , gameState_(GS_INTRO)
    , neededGameState_(GS_INTRO)
{
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Global, HandlePostUpdate));
}

// Метод устанавливает текущий счет и включает флаг, сигнализирующий о том,
// что необходимо обновить соответсвующий ему текстовый элемент на экране
void Global::SetScore(int score)
{
    if (score_ == score)
        return;

    score_ = score;
    scoreTextDirty_ = true;
}

// Игровой счет меняется в событии Update, поэтому мы используем событие,
// которое вызывается после него
void Global::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    // При необходимости обновляем текстовый элемент
    if (scoreTextDirty_)
    {
        Text* scoreText = static_cast<Text*>(UI_ROOT->GetChild("Score", false));

        String str = "Счёт: ";
        scoreText->SetText(str + String(score_));
        scoreTextDirty_ = false;
    }
}

/*

ПРИМЕЧАНИЕ

Игровой счет меняется только в одном месте программы, поэтому мы могли бы обновлять соответствующий ему
текстовый элемент сразу же. Данный пример - это демонстрация подхода для случаев, когда какие-то
значения могут изменяться (увеличиваться и уменьшаться) в разных частях программы,
и мы хотели бы избежать лишних обновлений для соответсвующих им элементов интерфейса.

*/
