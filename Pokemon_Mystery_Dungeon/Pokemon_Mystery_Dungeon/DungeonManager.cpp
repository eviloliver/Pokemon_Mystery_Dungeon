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
#include "BattleSystem.h"

void DungeonManager::Init()
{
    LoadDungeonData();
}

void DungeonManager::LoadDungeonData()
{
    // ���� �̸� �� ���� ���ϸ� ID + ���� ���� + ��
    // �ܺ� ���Ϸ� ���������� �ִ�
    // �ؿ��� ����
    dungeonSpawnMap["Volcano"] = DungeonSpawnInfo{{146,136, 76,75, 37, 150}, 10, 30, 4};

    dungeonSpawnMap["TinyForest"] = DungeonSpawnInfo{{133,10, 15, 18,151,149}, 3, 15, 4};

    dungeonSpawnMap["IceCave"] = DungeonSpawnInfo{ {130,25 ,135,7,8,9,52,64,94,143,144}, 5, 20, 4 };
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
    PlayerManager::GetInstance()->GetPlayer()->SetMap(dungeonMap);
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
    //��Ʋ �ý��ۿ��� pool����Ʈ�� �ʿ���
    BattleSystem::GetInstance()->SetPokemonPool(pool);

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
