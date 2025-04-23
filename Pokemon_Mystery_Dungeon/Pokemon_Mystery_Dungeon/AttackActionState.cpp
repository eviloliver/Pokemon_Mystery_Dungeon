#include "AttackActionState.h"

#include "ISkill.h"
#include "PokemonBase.h"

void AttackActionState::Enter(PokemonBase* owner)
{
    isFinished = false;

    direction = owner->GetDirection();

    // Check �̰� �Լ�ȭ �� �ʿ� �־��. ���� ���
    if (selectedSkill->GetAnimType() == "Rotate")
    {
        owner->PlayRotateAnim();
    }
    else if (selectedSkill->GetAnimType() == "Attack")
    {
        owner->PlayAttackAnim();
    }
    else
    {
        owner->PlaySwingAnim();
    }

    selectedSkill->Use(owner);
    duration = 1.f;
    // Check �ִϸ��̼� �� ��� �ð� -> �ϵ��ڵ� ���� �ٸ� ��� ���� �ʿ�
    // (PokemonBase������ AddAnimation �Ҷ� �ϵ� �ڵ� �Ǿ�����)
    elapsed = 0.f;

    /*   selectedSkill->Use();*/
}

void AttackActionState::Update(PokemonBase* owner)
{
    if (isFinished)
    {
        return;
    }
    if (selectedSkill)
    {
        selectedSkill->Update();
    }
    elapsed += TimerManager::GetInstance()->GetDeltaTime();

    if (elapsed >= duration)
    {
        isFinished = true;
        return;
    }
}

void AttackActionState::Exit(PokemonBase* owner)
{
}

bool AttackActionState::IsFinished()
{
    return isFinished;
}

bool AttackActionState::CanOverride()
{
    return isFinished;
}

void AttackActionState::SelectSkill(shared_ptr<ISkill> newSkill)
{
    selectedSkill = newSkill;
}

AttackActionState::AttackActionState()
{
    isFinished = false;
    selectedSkill = nullptr;
}
