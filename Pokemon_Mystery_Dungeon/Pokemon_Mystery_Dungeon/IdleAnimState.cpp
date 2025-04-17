#include "IdleAnimState.h"
#include "PokemonBase.h"
#include "PokemonAnimator.h"

void IdleAnimState::Enter(PokemonBase* owner)
{
	isFinished = false;
	owner->GetAnimator()->Play("Idle", owner->GetDirection());
}

void IdleAnimState::Update(PokemonBase* owner)
{
	owner->GetAnimator()->Update();
}

void IdleAnimState::Exit(PokemonBase* owner)
{

}

bool IdleAnimState::IsFinished()
{
	return isFinished;
}

bool IdleAnimState::CanOverride()
{
	// Idle�� �׻� ���º�ȯ ����
	// Idle can changes. always
	return true;
}

IdleAnimState::IdleAnimState()
{
	isFinished = false;
}
