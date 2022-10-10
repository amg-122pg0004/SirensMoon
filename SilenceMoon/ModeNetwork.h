#pragma once
#include "ModeBase.h"
#include <functional>
class Game;

class ModeNetwork :public ModeBase {
public:
	ModeNetwork(Game& game, ModeBase& mode);
	~ModeNetwork();
	void Update()override;
	void Render()override;
	void Debug()override;

	void UpdateSelectIndex();
	void SelectMenu();
	void CreateServer();
	void JoinServer();
	void Back();

private:
	
	bool _analogFlag;

	/*選択しているメニュー項番*/
	int _selectIndex;
	/*最大項番*/
	int _selectMAX;

	static char* IPDATAtoString(IPDATA ip);
	ModeBase& _preWindow;
	int _keyInputHandle;

	IPDATA _ip;
};
