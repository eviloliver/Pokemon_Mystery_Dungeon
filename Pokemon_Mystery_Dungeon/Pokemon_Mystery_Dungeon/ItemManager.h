#include"IItem.h"

class ItemManager
{
private:
    vector<unique_ptr<IItem>> items;

public:

    void SpawnRandomItem(); // ���� ������ ����
    void GetItem(/*Player* player*/);// �÷��̾��� ��ġ�� �浹 �˻� �� �÷��̾ ����
    void Update(/*Player* player*/);
    void Render(); //�ʿ� ������ ����
};
