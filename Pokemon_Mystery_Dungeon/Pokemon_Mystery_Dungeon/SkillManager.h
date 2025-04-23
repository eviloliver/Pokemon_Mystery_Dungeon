#pragma once
#include "GameObject.h"
#include "ISkill.h"
#include "Singleton.h"

class SkillManager : public Singleton<SkillManager>
{
private:
    map<string, shared_ptr<ISkill>> skillMap;
    shared_ptr<ISkill> skill;  // ����� ��ų ����
    string token;
    SkillData data;
    string line;
    int lineNumber;

public:
    void LoadSkillsFromCSV(const string& filepath);
    shared_ptr<ISkill> CreateSkill(const string& name);
    shared_ptr<ISkill> FindSkill(const string& name);
    void Release();
};
