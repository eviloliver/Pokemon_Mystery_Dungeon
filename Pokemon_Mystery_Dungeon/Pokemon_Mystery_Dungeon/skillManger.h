#pragma once
#include <string>
using namespace std;

enum class SkillType
{
    Physical,
    Special,
    Status // ��ȭ ���
};

class skillManger
{
public:
    skillManger(string name, string description, SkillType type,
        int power, int accuracy, int maxPP);

    void Use();                     // ��ų ���
    bool CanUse() const;            // PP�� ���� �ִ��� Ȯ��
    void ResetPP();                 // PP �ʱ�ȭ

    const std::string& GetName() const;
    const std::string& GetDescription() const;
    SkillType GetType() const;
    int GetPower() const;
    int GetAccuracy() const;
    int GetCurrentPP() const;
    int GetMaxPP() const;

private:
    string mName;
    string mDescription;
    SkillType mType;

    int mPower;     // ��� ����
    int mAccuracy;  // ��� ���߷�
    int mMaxPP;     // pp��
    int mCurrentPP;
};
