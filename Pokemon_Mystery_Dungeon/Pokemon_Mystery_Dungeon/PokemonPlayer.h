#pragma once
#include "PokemonBase.h"

class Item;
class PokemonPlayer : public PokemonBase
{
private:
 
    // ������ �κ��丮
    // vector<Item*> inventory;

    int exp = 0;
    int expToLevelUp;
    // int inventorySize = 20;
protected:

public:
    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;

    // ������ ���� �ൿ ó��
    bool CanPickUpItem() const;
    void PickUpItem(Item* item);
    void AddItemToBag(Item* item);
    void UseItem(Item* item);

    // ���� ����
    void GainExp(int amount);
    void LevelUp();
};

