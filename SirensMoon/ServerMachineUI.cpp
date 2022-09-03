#include "ServerMachineUI.h"
#include "Game.h"
#include "ServerMachine.h"
#include "SoundServer.h"

ServerMachineUI::ServerMachineUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size, ServerMachine& owner, EnemyGenerator::EnemyPattern pattern)
	:UIBase{game,mode,pos,size},_visible{false},_owner{owner}
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/UI/wanted.png");
	SetCGHandle(pattern);
}

void ServerMachineUI::Update() {
	if (_visible != _owner.GetValidFlag()) {
		_visible = _owner.GetValidFlag();
		if (_visible) {
			PlaySoundMem(SoundServer::Find("ServerAccess"), DX_PLAYTYPE_BACK);
			PlaySoundMem(SoundServer::Find("ServerAccessNow"), DX_PLAYTYPE_LOOP);
		}
		else {
			StopSoundMem(SoundServer::Find("ServerAccessNow"));
		}
	}

	if (_game.GetFrameCount() % 30 == 0) {
		++_animNo;
		if (_animNo >= 8) {
			_animNo = 0;
		}
	}
}

void ServerMachineUI::Render() {
	if (_visible) {

		Vector2 chara_posfix{ -200,-80 };
		Vector2 chara_size{ 700,700 };
		int alpha = _owner.GetEnergy();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y), GetColor(0, 0, 0), 1);
		DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y), _cg, 1);

		DrawExtendGraph(static_cast<int>(_pos.x)+ chara_posfix.x,
			static_cast<int>(_pos.y) + chara_posfix.y,
			static_cast<int>(_pos.x) + chara_posfix.x + chara_size.x,
			static_cast<int>(_pos.y) + chara_posfix.y + chara_size.y,
			_cg_bot[_animNo]
			, 1);
		DrawExtendGraph(static_cast<int>(_pos.x) + chara_posfix.x,
			static_cast<int>(_pos.y) + chara_posfix.y,
			static_cast<int>(_pos.x) + chara_posfix.x + chara_size.x,
			static_cast<int>(_pos.y) + chara_posfix.y + chara_size.y,
			_cg_top2[_animNo]
			, 1);
		DrawExtendGraph(static_cast<int>(_pos.x) + chara_posfix.x,
			static_cast<int>(_pos.y) + chara_posfix.y,
			static_cast<int>(_pos.x) + chara_posfix.x + chara_size.x,
			static_cast<int>(_pos.y) + 600,
			_cg_mid[_animNo]
			, 1);
		DrawExtendGraph(static_cast<int>(_pos.x) + chara_posfix.x,
			static_cast<int>(_pos.y) + chara_posfix.y,
			static_cast<int>(_pos.x) + chara_posfix.x + chara_size.x,
			static_cast<int>(_pos.y) + chara_posfix.y + chara_size.y,
			_cg_top[_animNo]
			, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void ServerMachineUI::SetCGHandle(EnemyGenerator::EnemyPattern pattern){

	std::string head2path{ "resource/Enemy/2_head" };
	switch (pattern.head) {
	case 1:
	case 3:
	case 7:
	case 8:
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		break;
	case 2:
	case 4:
	case 5:
	case 6:
	case 9:
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/2.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/3.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/4.png"));
		_cg_top2.push_back(ImageServer::LoadGraph("resource/Enemy/blank.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/6.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/7.png"));
		_cg_top2.push_back(ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/8.png"));
		break;
	}
	std::string headpath{ "resource/Enemy/head" };
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/1.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/2.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/3.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/4.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/5.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/6.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/7.png"));
	_cg_top.push_back(ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/8.png"));
	std::string bodypath{ "resource/Enemy/body" };
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/1.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/2.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/3.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/4.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/5.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/6.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/7.png"));
	_cg_mid.push_back(ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/8.png"));
	std::string footpath{ "resource/Enemy/foot" };
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/1.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/2.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/3.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/4.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/5.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/6.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/7.png"));
	_cg_bot.push_back(ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/8.png"));
}
