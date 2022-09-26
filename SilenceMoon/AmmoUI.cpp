#include "AmmoUI.h"
//#include "ModeBase.h"
#include "ModeGame.h"
#include  "PlayerA.h"
#include "Game.h"

class SplitWindow;

AmmoUI::AmmoUI(Game& game , ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase(game,mode, window, pos,size),_bullet1{0},_bullet2{9},_charge{0}
{
	_visible = true;
	_cg = ImageServer::LoadGraph("resource/UI/Ammo/base.png");
	_cg_mark = ImageServer::LoadGraph("resource/UI/Ammo/mark.png");
	_cg_gun = ImageServer::LoadGraph("resource/UI/Ammo/gun.png");
	_cg_line = ImageServer::LoadGraph("resource/UI/Ammo/line.png");
	_cg_empty= ImageServer::LoadGraph("resource/UI/Ammo/Empty.png");

	_cg_number1.resize(10);
	ImageServer::LoadDivGraph("resource/UI/Ammo/number_1.png",10,2,5,480,180,_cg_number1.data());
	_cg_number2.resize(10);
	ImageServer::LoadDivGraph("resource/UI/Ammo/number_2.png", 10, 2, 5, 480,180, _cg_number2.data());
	_cg_charge.resize(3);
	ImageServer::LoadDivGraph("resource/UI/Ammo/bar.png", 3, 1, 3, 480, 180, _cg_charge.data());
}

void AmmoUI::Update() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::PlayerA) {
			_bullet1=dynamic_cast<PlayerA&>(*actor).GetAmmo();
			_charge = dynamic_cast<PlayerA&>(*actor).GetCharge();
			if (_charge > 120) { 
				_charge = 120;
			}
		}
	}
}

void AmmoUI::Render(){
	if (!_visible) {
		return;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg, 1);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg_gun, 1);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg_line, 1);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg_mark, 1);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg_number1[_bullet1], 1);
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg_number2[5], 1);


	double alpha{ 255 };
	

	int render_gage{ 3 };
	SetDrawArea(static_cast<int>(_pos.x+140), static_cast<int>(_pos.y),
		static_cast<int>(_pos.x + 140 + (_size.x - 140-92) * (static_cast<double>(_charge) / 120)), static_cast<int>(_pos.y + _size.y));
	
	if (_charge >= 120) {
		alpha = (std::sin(_game.GetFrameCount() / 10) + 1) * 0.5 * 150 + 105;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha));
	}

	for (int i = 0; i < render_gage; ++i) {
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _cg_charge[i], 1);
	}
	auto&& window =dynamic_cast<ModeGame&>(_mode).GetSplitWindow();
	SetDrawArea(0, 0, screen_W, screen_H);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	if (_bullet1 <= 1) {
		DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y + 180), _cg_empty, 1);
	}
}
