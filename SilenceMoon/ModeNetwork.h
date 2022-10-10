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

	/*‘I‘ğ‚µ‚Ä‚¢‚éƒƒjƒ…[€”Ô*/
	int _selectIndex;
	/*Å‘å€”Ô*/
	int _selectMAX;

	static char* IPDATAtoString(IPDATA ip);
	ModeBase& _preWindow;
	int _keyInputHandle;

	IPDATA _ip;
};
