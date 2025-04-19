#pragma once
#include "SkillManager.h"

// ��ų ��� (�̸��� ��ų ��ü�� ���)
void SkillManager::RegisterSkill(const string& name, shared_ptr<ISkill> skill)
{
	skillMap[name] = skill;
}

// ��ų ��� (����ڿ� ��󿡰� ��ų ���)
void SkillManager::UseSkill(const string& skillName, GameObject* user, GameObject* target)
{
	auto it = skillMap.find(skillName);
	if (it != skillMap.end())
	{
		it->second->Use(user, target);
	}
}

void SkillManager::Release()
{
	skillMap.clear();
}

// ��ų ���� (���⼱ �̹� ��ϵ� ��ų�� ��ȯ)
shared_ptr<ISkill> SkillManager::CreateSkill(const string& name)
{
	auto it = skillMap.find(name);
	if (it != skillMap.end())
	{
		return it->second->Clone();  // ��ų �������� ��ȯ
	}
	return nullptr;
}

// ��ų ã�� (�̸����� ��ų ��ȯ)
shared_ptr<ISkill> SkillManager::FindSkill(const string& name)
{
	auto it = skillMap.find(name);
	if (it != skillMap.end())
	{
		return it->second;  // ��ų ��ü ��ȯ
	}
	return nullptr;
}

