#include "EmberSkill.h"

HRESULT EmberSkill::Init()
{
	pos.x = 100;
	pos.y = 100;
	name = "Ember";
	stats.power = 40;
	stats.accuracy = 100;
	stats.maxPP = 25;

	isActive = false;
	frameCount = 0;
	elapsedTime = 0.0f;
	image = ImageManager::GetInstance()->AddImage(
		"Ember", TEXT("Image/SkillImage/FireBlast.bmp"), 1856*2, 61*2 ,29, 1,
		true, RGB(255, 0, 255));

	return S_OK;
}

void EmberSkill::Release()
{
}

// EmberSkill::Update() �� ����
void EmberSkill::Update()
{
	if (isActive)
	{
		elapsedTime += TimerManager::GetInstance()->GetDeltaTime(); // ����

		if (elapsedTime >= 0.02f) // 0.2�ʸ��� ����
		{
			frameCount++;
			elapsedTime = 0.0f; // �ٽ� 0���� �ʱ�ȭ
		}

		if (frameCount >= image->GetMaxFrameX())
		{
			isActive = false;
			frameCount = 0;
		}
	}
}



void EmberSkill::Render(HDC hdc)
{
	if (isActive && image)
	{
		int frameX = frameCount;
		if (frameX >= image->GetMaxFrameX()) frameX = image->GetMaxFrameX() - 1;

		image->FrameRender(hdc, pos.x, pos.y, frameX, 0);
	}
}


void EmberSkill::Use(PlayerBumin* user, EnemyBumin* target)
{
	pos.x = target->GetX();
	pos.y = target->GetY();
	int emberDamage = 10; //fix ������ ��� �� ���� �ʿ�

	int newHP = target->GetHP() - emberDamage;
	if (newHP < 0)
		newHP = 0;

	target->SetHP(newHP);

	// ��ų ȿ�� Ȱ��ȭ
	isActive = true;
}


shared_ptr<ISkill> EmberSkill::Clone() const
{
	return make_shared<EmberSkill>(*this); // ��ų�� �����Ͽ� ��ȯ
}
