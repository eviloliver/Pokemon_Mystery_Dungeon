#pragma once
#include "ISkill.h"
#include "config.h"
#include "Image.h"

class Image;
class PokemonBase;
class EmberSkill : public ISkill {
private:
	Image* image;
	FPOINT pos;
	string name;
	SkillData data;
	int direction;
	bool isActive;

	float elapsedTime;
	bool isActive;  // ��ų ȿ���� Ȱ��ȭ�Ǿ� �ִ��� ����
	int frameCount;  // �ִϸ��̼� ������ ī��Ʈ (�ʿ��� ���)

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Use(PokemonBase* owner) const override;
	shared_ptr<ISkill> Clone() const override;
};
