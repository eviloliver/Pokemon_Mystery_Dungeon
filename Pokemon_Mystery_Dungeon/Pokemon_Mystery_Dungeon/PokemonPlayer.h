#pragma once
#include "PokemonBase.h"

class Item;
class ISkill;
class PokemonPlayer : public PokemonBase
{
private:
    // ������ �κ��丮
    // vector<Item*> inventory;

    int exp = 0;
    int expToLevelUp;
    // int inventorySize = 20;
    
    // SquareScene ����
    bool isInSquare = false;
    SIZE size = {TILE_SIZE, TILE_SIZE};
    RECT rect;
    float speed = 1;
    POINT prevPos = POINT{static_cast<int>(pos.x),
                          static_cast<int>(pos.y)};  // ���� ������ ��ġ
    

protected:
public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;

    // SquareScene ����
    void SquareModeMove();
    void UpdateRect();
    void SavePrevPos()
    {
        prevPos = POINT{static_cast<int>(pos.x), static_cast<int>(pos.y)};
    }
    void UndoMove()
    {
        pos = FPOINT{static_cast<float>(prevPos.x), static_cast<float>(prevPos.y)};
        UpdateRect();
    }

    RECT GetRect() const
    {
        return rect;
    }
    void IsInSquare(bool isFree)
    {
        isInSquare = isFree;
    }

    // ������ ���� �ൿ ó��
    bool CanPickUpItem() const;
    void PickUpItem(Item* item);
    void AddItemToBag(Item* item);
    void UseItem(Item* item);

    // ���� ����
    void GainExp(int amount);
    void LevelUp();
    void PrintLevelUpSummaryDialogue(const PokemonData& prevStatus,
                                     const PokemonData& newStatus);

    // ��ȭ ����
    void TryEvolve();
    void EvolveTo(int newPokemonId);

};
