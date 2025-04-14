#include "PokemonBase.h"
#include "PokemonDataLoader.h"
#include "PokemonImageLoader.h"
#include "Image.h"
#include "PokemonAnimator.h"

HRESULT PokemonBase::Init()
{
    baseStatus = PokemonDataLoader::GetInstance()->GetData(6);
    currentStatus = *baseStatus;
    level = 5; // ���� ����
    CalStatus();
    currentHp = currentStatus.hp;
    animator = new PokemonAnimator();
    string idStr = PokemonImageLoader::GetInstance()->PokemonIdToString(baseStatus->idNumber);
    for (auto type = animTypes.begin(); type != animTypes.end(); ++type)
    {
        string key = idStr + *type;
        Image* image = ImageManager::GetInstance()->FindImage(key);
        if (image) {
            int frameX = image->GetMaxFrameX();
            int frameY = image->GetMaxFrameY();
            float frameTime = 0.1f;
            animator->AddAnimation(*type, image, frameX, frameY, frameTime, *type == "Idle");
        }
    }
    return S_OK;
}

void PokemonBase::Release()
{
    if (animator)
    {
        animator->Release();
        delete animator;
        animator = nullptr;
    }

}

void PokemonBase::Update()
{
    animator->Update();
}

void PokemonBase::Render(HDC hdc)
{
    animator->Render(hdc, pos.x, pos.y);
}

void PokemonBase::CalStatus()
{
    currentStatus.hp = CalStat(baseStatus->hp) + 10/*������*/;
    currentStatus.atk = CalStat(baseStatus->atk) + 5/*������*/;
    currentStatus.def = CalStat(baseStatus->def) + 5/*������*/;
    currentStatus.spAtk = CalStat(baseStatus->spAtk) + 5/*������*/;
    currentStatus.spDef = CalStat(baseStatus->spDef) + 5/*������*/;
    currentStatus.speed = CalStat(baseStatus->speed) + 5/*������*/;
}

int PokemonBase::CalStat(int value)
{
    return (value + IV + EV + 100) * level / 100;
}