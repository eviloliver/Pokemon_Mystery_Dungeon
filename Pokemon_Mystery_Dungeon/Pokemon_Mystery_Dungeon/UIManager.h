#pragma once
#include "UIState.h"
#include "Singleton.h"

class UIManager : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

private:
	map<string, UIState*> UiStateMap; // UI ���¸� �����ϴ� ��
	map<string, bool> IsOpenMap;
	string currentStateKey;

public:
	static UIState* currentState;
	static UIState* nextState;

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	HRESULT ChangeState(string key);
	UIState* AddState(string key, UIState* state);
	UIState* FindState(const string& key);
	void RegisterAllUIStates();
	void OpenUIStateBox(const string& key);
	void CloseUIStateBox(const string& key);



};

