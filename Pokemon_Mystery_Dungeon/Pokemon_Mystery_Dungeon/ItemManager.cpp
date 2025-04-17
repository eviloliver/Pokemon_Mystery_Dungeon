#include "ItemManager.h"

void ItemManager::SpawnRandomItem()
{
	//���� ��ġ�� �޾Ƽ� ������ ����
}

void ItemManager::GetItem(Player* player)
{
    for (auto it = items.begin(); it != items.end(); )
    {
        POINT playerPos = player->GetPosition();
        IItem* item = it->get(); // IItem ������

        if (playerPos.x == item->GetX() && playerPos.y == item->GetY())
        {
            std::string itemName = item->GetName();

            player->AddItem(itemName); // �̸� ������� �߰�

            it = items.erase(it); // unique_ptr �ڵ� ������
        }
        else
        {
            ++it;
        }
    }
}




void ItemManager::Update()
{

}

void ItemManager::Render()
{

}
