#include "IdleAnimState.h"
#include "PokemonBase.h"
#include "PokemonAnimator.h"

void IdleAnimState::Enter(PokemonBase* outer)
{
	finished = false;
	outer->GetAnimator()->Play("Idle", outer->GetDirection());
}

void IdleAnimState::Update(PokemonBase* outer)
{
	outer->GetAnimator()->Update();
}

void IdleAnimState::Exit(PokemonBase* outer)
{

}

bool IdleAnimState::IsFinished()
{
	return finished;
}

bool IdleAnimState::CanOverride()
{
	// Idle�� �׻� ���º�ȯ ����
	// Idle can changes. always
	return true;
}

IdleAnimState::IdleAnimState()
{
	finished = false;
}
