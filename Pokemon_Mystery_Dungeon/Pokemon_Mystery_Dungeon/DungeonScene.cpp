#include "DungeonScene.h"

#include "BossScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MPlayer.h"
#include "UIManager.h"
#include "Camera.h"
#include "PokemonPool.h"
#include "TurnManager.h"
#include "DungeonManager.h"
#include "Map.h"
#include "PlayerManager.h"
#include "PokemonPlayer.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "FadeManager.h"
#include "SquareScene.h"
#include "CoolDownManager.h"

HRESULT DungeonScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    dungeonMap = new Map();
    dungeonMap->Init();

    dungeonManager = new DungeonManager();
    dungeonManager->Init();
    dungeonManager->SetDungeonMap(dungeonMap);
    EnterDungeonType();

    Camera::GetInstance()->SetMapSize({TILE_X * TILE_SIZE, TILE_Y * TILE_SIZE});
    Camera::GetInstance()->SetScreenSize({500, 400});

    wallTiles = dungeonMap->GetWallTiles();  // wallTiles��ǥ  Point��

    dungeonFloor = 0;
    elapsedTime = 0.f;

    GenerateNextFloor();
    FadeManager::GetInstance()->StartFadeIn();
    return S_OK;
}

void DungeonScene::Release()
{
    if (dungeonManager)
    {
        dungeonManager->ExitDungeon();
        delete dungeonManager;
        dungeonManager = nullptr;
    }
    if (dungeonMap)
    {
        delete dungeonMap;
        dungeonMap = nullptr;
    }

}

void DungeonScene::Update()
{
    float dt = TimerManager::GetInstance()->GetDeltaTime();

    if (dungeonMap)
    {
        dungeonMap->Update();
    }
    if (pool)
    {
        pool->Update();
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_TAB))
    {
        if (UIManager::GetInstance()->GetCurrentStateKey() != "defaultUI")
            UIManager::GetInstance()->OpenUIStateBox("defaultUI");
    }


    TurnManager::GetInstance()->Update();

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6))
    {
        SceneManager::GetInstance()->ChangeScene("Square");
    }


    if (isSceneTransition && FadeManager::GetInstance()->IsFadeComplete())
    {
        GenerateNextFloor();
        FadeManager::GetInstance()->StartFadeIn(1.0);
        isSceneTransition = false;
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE) &&!FadeManager::GetInstance()->IsFading())
    {
        FadeManager::GetInstance()->StartFadeOut(1.0);
        isSceneTransition = true;
    }
    if (dungeonFloor > 3)
    {
        SceneManager::GetInstance()->ChangeScene("Square");
        dungeonFloor = 0;
    }
    if (dungeonFloor > 2)
    {
        if (UIManager::GetInstance()->GetDungeonType() == DUNGEON_TYPE_ICE)
        {
            dungeonMap->SetTileImage(dungeonMap->GetNextIceTileImage());
        }
        else if (UIManager::GetInstance()->GetDungeonType() == DUNGEON_TYPE_MAGMA)
        {
            dungeonMap->SetTileImage(dungeonMap->GetNextMagmaTileImage());
        }
        else if (UIManager::GetInstance()->GetDungeonType() == DUNGEON_TYPE_FOREST)
        {
            dungeonMap->SetTileImage(dungeonMap->GetNextTiniTileImage());
        }
    }



    elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
    if (elapsedTime > 0.016f)
    {
        FadeManager::GetInstance()->Update();
        Camera::GetInstance()->Update(elapsedTime);
        elapsedTime = 0;
    }


    // �÷��̾� ������� ui����.
    CoolDownManager::GetInstance()->Update(dt);
    
    if (!CoolDownManager::GetInstance()->IsCooldown("DownStair") && IsPlayerOnStair() &&
        UIManager::GetInstance()->GetCurrentStateKey() != "DownStairUI")
    {
        UIManager::GetInstance()->OpenUIStateBox("DownStairUI");
    }

    if (UIManager::GetInstance()->IsDownStairUIActive())    //�Ѿ�°� yes�� Ŭ���ߴٸ�, 
    {   
        GenerateNextFloor();
        FadeManager::GetInstance()->StartFadeIn(1.0);
        isSceneTransition = false;
    }
}

void DungeonScene::Render(HDC hdc)
{
    HRGN clipRegion = CreateRectRgn(0, 0, 500, 400);
    SelectClipRgn(hdc, clipRegion);


    if (dungeonMap)
    {
        dungeonMap->RenderWithCamera(hdc);
        dungeonMap->MiniMapRender(hdc, 0, 0);
    }
    if (pool)
    {
        pool->Render(hdc);
    }

    SelectClipRgn(hdc, NULL);
    DeleteObject(clipRegion);


    //UI�� clip���� �ۿ� �߰��ϽǰŸ� �� �ؿ� �μ��� --
    UIManager::GetInstance()->Render(hdc);
    FadeManager::GetInstance()->Render(hdc, 500, 400);
}

void DungeonScene::GenerateNextFloor()
{
    dungeonManager->ExitDungeon();
    dungeonMap->Init();
    EnterDungeonType();
    wallTiles = dungeonMap->GetWallTiles();
    stairPos = ConvertToPixel(dungeonMap->GetStairPos());

    //ui���� ���¹ٲ�
    UIManager::GetInstance()->SetDownStairUIActive(false);
    ++dungeonFloor;
}

POINT DungeonScene::ConvertToPixel(POINT tilePos)
{
    tilePos.x *= TILE_SIZE;
    tilePos.y *= TILE_SIZE;
    return tilePos;
}

bool DungeonScene::IsPlayerOnStair()
{
    FPOINT playerPos = PlayerManager::GetInstance()->GetPlayer()->GetPos();
    return abs(playerPos.x - stairPos.x) <= TILE_SIZE-5 &&
           abs(playerPos.y - stairPos.y) <= TILE_SIZE-5;
}

void DungeonScene::EnterDungeonType()
{
    if (UIManager::GetInstance()->GetDungeonType() == DUNGEON_TYPE_FOREST)
    {
        dungeonManager->EnterDungeon("TinyForest");

    }
    else if (UIManager::GetInstance()->GetDungeonType() == DUNGEON_TYPE_ICE)
    {
        dungeonManager->EnterDungeon("IceCave");

    }
    else if (UIManager::GetInstance()->GetDungeonType() == DUNGEON_TYPE_MAGMA)
    {
        dungeonManager->EnterDungeon("Volcano");
    }
    UIManager::GetInstance()->ChangeState("IdleUI");

    pool = dungeonManager->GetPokemonPool();
    TurnManager::GetInstance()->InitTurnOrder(pool);

}
