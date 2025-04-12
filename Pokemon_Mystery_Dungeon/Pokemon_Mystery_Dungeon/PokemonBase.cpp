#include "PokemonBase.h"
#include "PokemonDataLoader.h"

HRESULT PokemonBase::Init()
{
    baseStatus = PokemonDataLoader::GetInstance()->GetData(1);
    currentStatus = *baseStatus;
    level = 5; // ���� ����
    CalStatus();
    currentHp = currentStatus.hp;
    return S_OK;
}

void PokemonBase::Release()
{
}

void PokemonBase::Update()
{
}

void PokemonBase::Render(HDC hdc)
{
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