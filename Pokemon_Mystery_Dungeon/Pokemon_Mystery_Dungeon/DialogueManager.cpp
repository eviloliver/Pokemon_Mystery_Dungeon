#define _HAS_STD_BYTE 0
#include <Windows.h>
#undef byte


#include "DialogueManager.h"
#include "UIManager.h"
#include "DialogueUIState.h"
#include "DialogueTemplate.h"


// text: ���ø� ���ڿ� (��: "'�����۸�'�� ȹ���߽��ϴ�")
// values: ���ø����� ġȯ�� ���� ���� (��: { {"�����۸�", "���ͺ�"} })
void DialogueManager::ShowLine(const wstring& templateText, const map<wstring, wstring>& values)
{
    // ��ȭâ ���·� ��ȯ
    UIManager::GetInstance()->ChangeState("dialogueBox");

    // ���� ���¸� DialogueUIState�� ĳ�����ؼ� ã��
    auto* state = dynamic_cast<DialogueUIState*>(UIManager::GetInstance()->FindState("dialogueBox"));
    if (state)
    {
        // �ؽ�Ʈ + ġȯ map ����
        state->PushDialogueLine(templateText, values);
    }
}

/*
* ���� �򰥷��� ���� �ٽ� ������ �����ص� �ּ�

- dynamic_cast�� ����ϴ� ����:
    UIManager�� ��� UI ���¸� ���� Ÿ���� UIState*�� ������
    ������ ��ȭâ������ ����ϴ� PushDialogueLine() ���� �Լ���
    UIState*�δ� ����� �� ���� ������
    ���� Ÿ���� DialogueUIState���� Ȯ���ؼ� �����ϰ� ����ȯ�ؾ� ��
    �� �װ� dynamic_cast

    dynamic_cast�� "�� UI�� ��¥ ��ȭ���� �¾�?"��� üũ�ϰ� ��ȯ���ִ� ������ ������
    �� ���� �� Ÿ�� �� ���� ���� ����ż� ũ���� �� �� ����.

- ����:
    auto* state = dynamic_cast<DialogueUIState*>(UIManager::GetInstance()->FindState("dialogueBox"));

- ���� ���� �ϰ� �;��� ����:
    if (I Ű�� ������)
    {
        ��ȭ���ڸ� �����;
        ��� �� ���� �߰��Ѵ�;
        ȭ�鿡 �׸���;
    }

    �� �� ������ ���⿣ ����������,
      ��ȭ �α׸� ��� ������ ��ȭâ�� ���� �����,
      Init(), Update(), Render()�� �Ź� ���� ȣ���ؾ� ��

    �� ���� ������ ��ȭâ�� UIManager�� �� ���� ����� �������ְ�,
      �� �׳� ��� �� �ٸ� �߰��ϸ� ��
      �ڵ�� ��� ��������, �ξ� ȿ�����̰� ������ ������ ���ذ� �����
*/
