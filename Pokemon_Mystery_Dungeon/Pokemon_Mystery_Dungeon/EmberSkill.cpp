#include "EmberSkill.h"
#include "PokemonBase.h"



EmberSkill::EmberSkill(const SkillData& skillData)
{
	data = skillData;
}
   
HRESULT EmberSkill::Init()
{
	pos = { 0,0 };
	isActive = false;
	frameCount = 0;
	elapsedTime = 0.0f;
	image = ImageManager::GetInstance()->AddImage(
		"Ember", TEXT("Image/SkillImage/FireBlast.bmp"), 1856/2, 61/2, 29, 1,
		true, RGB(255, 0, 255));

	return S_OK;
}

void EmberSkill::Release()
{

}

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

void EmberSkill::Use(PokemonBase* owner)
{
	direction = static_cast<int>(owner->GetDirection());
	pos = owner->GetPos();
	auto dirIndex = static_cast<size_t>(direction);

	// ���� ����
	pos.x += directionOffsets[dirIndex].first * 24;
	pos.y += directionOffsets[dirIndex].second * 24;

	isActive = true;

}




shared_ptr<ISkill> EmberSkill::Clone()
{
	return make_shared<EmberSkill>(*this); // ��ų�� �����Ͽ� ��ȯ
}

