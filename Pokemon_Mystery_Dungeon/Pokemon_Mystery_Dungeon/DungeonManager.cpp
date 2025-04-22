#include "DungeonManager.h"

#include "CommonFunction.h"
#include "PlayerManager.h"
#include "PokemonAnimator.h"
#include "PokemonBuilder.h"
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
    dungeonSpawnMap["Volcano"] = DungeonSpawnInfo{{4, 5, 37}, 5, 10, 10};

    dungeonSpawnMap["TinyForest"] = DungeonSpawnInfo{{10, 13, 16}, 3, 6, 8};
}

void DungeonManager::EnterDungeon(string dungeonName)
{
    pool = new PokemonPool();
    pool->Init();

    builder = new PokemonBuilder();
    builder->SetPool(pool);

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

    // �� ����
    for (int i = 0; i < info.spawnCount; ++i)
    {
        PokemonBase* enemy = builder->BuildFromDungeonInfo(info);
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
