#include "DungeonManager.h"

#include "CommonFunction.h"
#include "PlayerManager.h"
#include "PokemonAnimator.h"
#include "PokemonBuilder.h"
#include "PokemonEnemy.h"
#include "PokemonImageLoader.h"
#include "PokemonPlayer.h"
#include "PokemonPool.h"
#include "TurnManager.h"

void DungeonManager::Init()
{
    LoadDungeonData();
}

void DungeonManager::LoadDungeonData()
{
    // ���� �̸� �� ���� ���ϸ� ID + ���� ���� + ��
    // �ܺ� ���Ϸ� ���������� �ִ�
    // �ؿ��� ����
    dungeonSpawnMap["Volcano"] = DungeonSpawnInfo{{4, 5, 37}, 5, 10, 4};

    dungeonSpawnMap["TinyForest"] = DungeonSpawnInfo{{10, 13, 16}, 3, 6, 4};
}

void DungeonManager::EnterDungeon(string dungeonName)
{
    pool = new PokemonPool();
    pool->Init();

    builder = new PokemonBuilder();
    builder->SetPool(pool);
    builder->SetMap(dungeonMap);

    if (dungeonSpawnMap.find(dungeonName) == dungeonSpawnMap.end())
    {
        return;
    }

    DungeonSpawnInfo& info = dungeonSpawnMap[dungeonName];

    // �̹��� �����
    for (int id : info.pokemonIds)
    {
        PokemonImageLoader::GetInstance()->LoadPokemonAnim(id);
    }

    // �÷��̾� ��ġ ����
    FPOINT playerPos = builder->GetRandomValidPosition();
    PlayerManager::GetInstance()->GetPlayer()->SetPos(playerPos);

    // �� ����
    for (int i = 0; i < info.spawnCount; ++i)
    {
        PokemonEnemy* enemy =
            static_cast<PokemonEnemy*>(builder->BuildFromDungeonInfo(info));
        // ĳ����
        if (enemy)
        {
            enemy->SetMap(dungeonMap);
        }
    }

    // �� �Ŵ������� Pool �ѱ��
    TurnManager::GetInstance()->InitTurnOrder(pool);
}

void DungeonManager::ExitDungeon()
{
    PokemonImageLoader::GetInstance()->ClearPokemonImage();

    int playerId = PlayerManager::GetInstance()
                       ->GetPlayer()
                       ->GetCurrentPokemonData()
                       .idNumber;

    PlayerManager::GetInstance()->GetPlayer()->GetAnimator()->Clear();
    PokemonImageLoader::GetInstance()->LoadPokemonAnim(playerId);
    PlayerManager::GetInstance()->GetPlayer()->SetAnimator();
    PlayerManager::GetInstance()->GetPlayer()->PlayIdleAnim();
    if (pool)
    {
        pool->Release();
        delete pool;
        pool = nullptr;
    }
    if (builder)
    {
        delete builder;
        builder = nullptr;
    }
}
