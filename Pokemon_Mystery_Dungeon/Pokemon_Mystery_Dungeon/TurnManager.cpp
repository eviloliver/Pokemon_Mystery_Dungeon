#include "TurnManager.h"
#include "PokemonBase.h"

void TurnManager::InitTurnOrder(vector<PokemonBase*>& pokemons)
{
}

PokemonBase* TurnManager::GetCurrentPokemon()
{
    return turnOrder[currentIndex];
}

bool TurnManager::IsPlayerTurn()
{
    if (currentIndex = 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void TurnManager::Update()
{
    if (turnOrder.empty()) 
    {
        return;
    }

    PokemonBase* current = GetCurrentPokemon();

    switch (state)
    {
    case TurnState::WaitingForInput:
        /*
        if (�÷��̾�����) IsPlayerTurn()
        {
            if(��ȿ�� �Է��� �ϸ�)
            {
            // �÷��̾� �ൿ ����
                state = TurnState::ExecutingAction;

            }
        }
        else
        {
            // AI �ൿ ����
            state = TurnState::ExecutingAction;
        }
        */  
        break;

    case TurnState::ExecutingAction:
        state = TurnState::WaitingForAnim;
        break;

    case TurnState::WaitingForAnim:
        elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
        if (elapsedTime >= 1.0f) // Check ���� �ð� ���
        {
            state = TurnState::TurnEnd;
        }
        break;

    case TurnState::TurnEnd:
        ++ currentIndex;
        state = TurnState::WaitingForInput;
        // �� �� ���
        break;
    }
}