#include "PokemonPool.h"

#include "PlayerManager.h"
#include "PokemonBase.h"
#include "PokemonEnemy.h"
#include "PokemonPlayer.h"
#include "ISkill.h"
#include <algorithm>

HRESULT PokemonPool::Init()
{
    pokemonPool.resize(20);
    pokemonPool[0] = PlayerManager::GetInstance()->GetPlayer();
    for (iterPokemonPool = begin(); iterPokemonPool != end(); ++iterPokemonPool)
    {
        if (iterPokemonPool == begin())
        {
            continue;
        }
        (*iterPokemonPool) = new PokemonEnemy;
        (*iterPokemonPool)->SetIsAlive(false);
    }
    return S_OK;
}

void PokemonPool::Release()
{
    for (iterPokemonPool = begin() + 1; iterPokemonPool != end();
         ++iterPokemonPool)
    {
        if (iterPokemonPool == begin())
        {
            continue;
        }
        delete (*iterPokemonPool);
        (*iterPokemonPool) = nullptr;
    }
}

void PokemonPool::Update()
{
    for (iterPokemonPool = begin(); iterPokemonPool != end(); ++iterPokemonPool)
    {
        if ((*iterPokemonPool)->GetIsAlive())
        {
            (*iterPokemonPool)->Update();
        }
    }
}

// GPT�� § �ڵ�
// ���߿� ���� �� ��
// GPT Code
// See Later
void PokemonPool::Render(HDC hdc)
{
    std::vector<RenderItem> renderQueue;

    // ���ϸ� �� ��ų ���
    for (auto& pokemon : pokemonPool)
    {
        bool isPlayer = (pokemon == PlayerManager::GetInstance()->GetPlayer());

        // ���� ������� ���� ����, �÷��̾�� �׾ ����
        if (pokemon && (pokemon->GetIsAlive() || isPlayer))
        {
            // ���ϸ� ���
            renderQueue.push_back({
                pokemon->GetPos().y,
                pokemon,
                false,
                nullptr  // ���ϸ��� shared_ptr �ʿ� ����
                });

            // ��ų ���
            for (int i = 0; i < 4; ++i)
            {
                std::shared_ptr<ISkill> skill = pokemon->GetSkill(i);
                if (skill && skill->IsActive())
                {
                    renderQueue.push_back({
                        skill->GetPos().y,
                        skill.get(),
                        true,
                        skill  // shared_ptr ���� ����
                        });
                }
            }
        }
    }

    // ��ų�� �׻� ����, ���� Ÿ���̸� Y ���� ����
    std::sort(renderQueue.begin(), renderQueue.end(), [](const RenderItem& a, const RenderItem& b) {
        if (a.isSkill != b.isSkill)
            return !a.isSkill;  // ���ϸ� ����, ��ų ���߿�
        return a.y < b.y;       // ���� Ÿ���̸� Y��ǥ ����
        });

    // ������
    for (auto& item : renderQueue)
    {
        if (item.isSkill)
        {
            ((ISkill*)item.object)->Render(hdc);
        }
        else
        {
            ((PokemonBase*)item.object)->Render(hdc);
        }
    }
}
PokemonBase* PokemonPool::Get()
{
    for (int i = 1; i < pokemonPool.size(); ++i)
    {
        if (!pokemonPool[i]->GetIsAlive())
        {
            return pokemonPool[i];
        }
    }
    return nullptr;
}

void PokemonPool::Return(PokemonBase* pokemon)
{
    if (pokemon)
    {
        pokemon->SetIsAlive(false);
    }
}

void PokemonPool::ReturnEnemies()
{
    for (int i = 1; i < pokemonPool.size(); ++i)
    {
        if (pokemonPool[i]->GetIsAlive())
        {
            pokemonPool[i]->SetIsAlive(false);
        }
    }
}

bool PokemonPool::IsEmpty()
{
    for (const auto& pokemon : pokemonPool)
    {
        if (pokemon && pokemon->GetIsAlive())
        {
            return false;
        }
    }
    return true;
}

bool PokemonPool::IsPositionBlocked(FPOINT pos)
{
    for (auto iter = pokemonPool.begin(); iter != pokemonPool.end(); ++iter)
    {
        if ((*iter)->GetIsAlive())
        {
            FPOINT otherPos = (*iter)->GetPos();
            if (abs(pos.x - otherPos.x) < TILE_SIZE &&
                abs(pos.y - otherPos.y) < TILE_SIZE)
            {
                return true;
            }
        }
    }
    return false;
}

// ���ᰡ ����� ��Ȳ������ ���� ������ ���� �ʿ��Ұ� ����