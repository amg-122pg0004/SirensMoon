#pragma once
#include "UIBase.h"
#include <vector>

class AmmoUI :public UIBase{
public:
	AmmoUI(Game&, ModeBase&, Vector2 pos, Vector2 size);
	void Update()override;
	void Render()override;

	Type GetType()override { return Type::Ammo; }
private:

	int _bullet1,_bullet2;
	int _charge;

	/*目盛りハンドル*/
	int _cg_mark;
	int _cg_gun;
	int _cg_line;

	/*チャージバー用ハンドル[0]~[2]*/
	std::vector<int> _cg_charge;
	/*数字画像ハンドル[0]~[9]*/
	std::vector<int> _cg_number1;
	std::vector<int> _cg_number2;
};
