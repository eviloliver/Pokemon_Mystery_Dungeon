#pragma once
#include "ISkill.h"
#include "config.h"
#include "Image.h"

class Image;
class EmberSkill : public ISkill {
private:
    Image* image;

    enum class ElementType { FIRE };
    enum class SkillType { SPECIAL };

    FPOINT pos;
    string name;
    struct SkillStats {
        int power;
        int accuracy;
        int maxPP;
    } stats;

    float elapsedTime;
    bool isActive;  // ��ų ȿ���� Ȱ��ȭ�Ǿ� �ִ��� ����
    int frameCount;  // �ִϸ��̼� ������ ī��Ʈ (�ʿ��� ���)

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    void Use(PlayerBumin* user, EnemyBumin* target) override;
    shared_ptr<ISkill> Clone() const override;

    string GetName() const override { return name; }
    string GetElement() const override { return "FIRE"; }
    string GetType() const override { return "SPECIAL"; }
    int GetPower() const override { return stats.power; }
    int GetAccuracy() const override { return stats.accuracy; }
};
