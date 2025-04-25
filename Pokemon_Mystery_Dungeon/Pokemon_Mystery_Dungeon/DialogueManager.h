#pragma once
#include <map>
#include <string>

#include "Singleton.h"

class DialogueManager : public Singleton<DialogueManager>
{
public:
    // �ؽ�Ʈ ���ø� + ġȯ ������ ��ȭ 1�� ���
    void ShowLine(const std::wstring& templateText,
                  const std::map<std::wstring, std::wstring>& values);

};
