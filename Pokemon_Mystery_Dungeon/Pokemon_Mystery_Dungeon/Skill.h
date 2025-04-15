#pragma once
#include "GameObject.h"
#include <functional>

enum class SkillType {  //���Ÿ�� �з�
    PHYSICAL,
    SPECIAL,
    STATUS
};

enum class SkillTarget {    //��� Ÿ�� ex)�÷��̾�->��
    ENEMY,
    PARTNER,
    PLAYER
};

class Unit; // ���ϸ� ����? ���漱�� �ٲ㵵 �� ���� ����

class Skill : public GameObject 
{
private:
    string name;            //����̸�
    SkillType type;         //���Ÿ��
    int power;              //�������
    int accuracy;           //���߷�
    int maxPP;              //�ִ� pp
    int currentPP;          //����� pp
    SkillTarget targetType; //Ÿ���� ����
    string description;     //�������

    function<void(Unit* user, Unit* target)> effect; //����� ���� ȿ�� �Լ�

public:
    Skill();
    ~Skill();

    void Init(const string& name, SkillType type, int power, int accuracy, int maxPP,
        SkillTarget targetType, const string& description,
        function<void(Unit* user, Unit* target)> effect);

    void Update();
    void Render(HDC hdc);
    void Release();

    void Use(Unit* user, Unit* target); // ��ų ����

    bool CanUse() const { return currentPP > 0; }   // pp�� �ִ��� Ȯ�� ����

    const string& GetName() const { return name; }
    const string& GetDescription() const { return description; }
    int GetCurrentPP() const { return currentPP; }
    int GetMaxPP() const { return maxPP; }
};
