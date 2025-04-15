#pragma once
#include "UIState.h"
#include "Singleton.h"

class UIManager : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

private:
	map<string, UIState*> UiStateMap; // UI ���¸� �����ϴ� ��

	UIManager() = default;
	~UIManager();

public:
	static UIState* currentState;
	static UIState* nextState;

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	HRESULT ChangeState(string key);
	void AddState(string key, UIState* state);

};

