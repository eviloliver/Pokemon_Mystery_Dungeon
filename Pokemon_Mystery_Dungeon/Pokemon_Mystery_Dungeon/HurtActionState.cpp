#include "HurtActionState.h"

#include "PokemonBase.h"

void HurtActionState::Enter(PokemonBase* owner)
{
    isFinished = false;

    duration = 1.f;
    // Check �ִϸ��̼� �� ��� �ð� -> �ϵ��ڵ� ���� �ٸ� ��� ���� �ʿ�
    // (PokemonBase������ AddAnimation �Ҷ� �ϵ� �ڵ� �Ǿ�����)
    elapsed = 0.f;

    owner->PlayHurtAnim();
}

void HurtActionState::Update(PokemonBase* owner)
{
    elapsed += TimerManager::GetInstance()->GetDeltaTime();

    if (elapsed >= duration)
    {
        isFinished = true;
        return;
    }
    if (owner->GetCurrentPokemonData().hp >= 0)
    {
        // ����� �����ý��� ����� �ؾ��ϳ� ����
    }
}

void HurtActionState::Exit(PokemonBase* owner)
{
}

bool HurtActionState::IsFinished()
{
    return isFinished;
}

bool HurtActionState::CanOverride()
{
    return isFinished;
}

HurtActionState::HurtActionState()
{
    isFinished = false;
}
