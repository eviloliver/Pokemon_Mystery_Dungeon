#pragma once
#include "UIState.h"
#include "Singleton.h"

class UIManager : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

private:
	map<string, UIState*> UiStateMap; // UI ���¸� �����ϴ� ��
	map<string, bool> IsOpenMap;


public:
	static UIState* currentState;
	static UIState* nextState;

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	HRESULT ChangeState(string key);
	UIState* AddState(string key, UIState* state);
	void RegisterAllUIStates();
	void OpenUIStateBox(const string& key);


};

