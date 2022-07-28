#include "ServerMachineUI.h"
#include "Game.h"
#include "ImageServer.h"
#include "ServerMachine.h"
#include "SoundServer.h"

ServerMachineUI::ServerMachineUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size, ServerMachine& owner)
	:UIBase{game,mode,pos,size},_visible{false},_owner{owner}
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/Map/map_frame.png");

	_cg_red1.resize(30);
	_cg_red2.resize(30);
	_cg_red3.resize(30);
	_cg_blue1.resize(30);
	_cg_blue2.resize(30);
	_cg_blue3.resize(30);
	_cg_green1.resize(30);
	_cg_green2.resize(30);
	_cg_green3.resize(30);
	ImageServer::LoadDivGraph("resource/Enemy/red_top2.png", 30, 5, 6, 250, 370, _cg_red1.data());
	ImageServer::LoadDivGraph("resource/Enemy/red_mid2.png", 30, 5, 6, 250, 370, _cg_red2.data());
	ImageServer::LoadDivGraph("resource/Enemy/red_bot2.png", 30, 5, 6, 250, 370, _cg_red3.data());
	ImageServer::LoadDivGraph("resource/Enemy/blue_top2.png", 30, 5, 6, 250, 370, _cg_blue1.data());
	ImageServer::LoadDivGraph("resource/Enemy/blue_mid2.png", 30, 5, 6, 250, 370, _cg_blue2.data());
	ImageServer::LoadDivGraph("resource/Enemy/blue_bot2.png", 30, 5, 6, 250, 370, _cg_blue3.data());
	ImageServer::LoadDivGraph("resource/Enemy/green_top2.png", 30, 5, 6, 250, 370, _cg_green1.data());
	ImageServer::LoadDivGraph("resource/Enemy/green_mid2.png", 30, 5, 6, 250, 370, _cg_green2.data());
	ImageServer::LoadDivGraph("resource/Enemy/green_bot2.png", 30, 5, 6, 250, 370, _cg_green3.data());
}

void ServerMachineUI::Update() {
	_visible = _owner.GetValidFlag();
}

void ServerMachineUI::Render() {

	


	if (_visible) {
		std::vector<int> cg_top{ -1 }, cg_mid{ -1 }, cg_bot{ -1 };

		auto pattern = _owner.GetGeneratedEnemy();

		switch (pattern[0]) {
		case 1:
			cg_top = _cg_red1;
			break;
		case 2:
			cg_top = _cg_blue1;
			break;
		case 3:
			cg_top = _cg_green1;
			break;
		}
		switch (pattern[1]) {
		case 1:
			cg_mid = _cg_red2;
			break;
		case 2:
			cg_mid = _cg_blue2;
			break;
		case 3:
			cg_mid = _cg_green2;
			break;
		}
		switch (pattern[2]) {
		case 1:
			cg_bot = _cg_red3;
			break;
		case 2:
			cg_bot = _cg_blue3;
			break;
		case 3:
			cg_bot = _cg_green3;
			break;
		}

		int alpha = _owner.GetEnergy();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y), _cg, 0);

		DrawGraph(static_cast<int>(_pos.x)+250, static_cast<int>(_pos.y)+130, cg_bot[_game.GetFrameCount()/10%30], 1);
		DrawGraph(static_cast<int>(_pos.x)+250, static_cast<int>(_pos.y)+130, cg_mid[_game.GetFrameCount()/10%30], 1);
		DrawGraph(static_cast<int>(_pos.x)+250, static_cast<int>(_pos.y)+130, cg_top[_game.GetFrameCount()/10% 30], 1);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}