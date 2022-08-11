#include "ServerMachineUI.h"
#include "Game.h"
#include "ServerMachine.h"
#include "SoundServer.h"

ServerMachineUI::ServerMachineUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size, ServerMachine& owner, EnemyGenerator::EnemyPattern pattern)
	:UIBase{game,mode,pos,size},_visible{false},_owner{owner}
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/UI/wanted.png");

	switch (pattern.head) {
	case 1:
		_cg_top = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_down.png");
		_cg_top2 = ImageServer::LoadGraph("resource/Enemy/blank.png");
		break;
	case 2:
		_cg_top = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_down.png");
		_cg_top2 = ImageServer::LoadGraph("resource/Enemy/blank.png");
		break;
	case 3:
		_cg_top = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_down.png");
		_cg_top2 = ImageServer::LoadGraph("resource/Enemy/blank.png");
		break;
	}
	switch (pattern.body) {
	case 1:
		_cg_mid = ImageServer::LoadGraph("resource/Enemy/body1/body1_down.png");
		break;
	case 2:
		_cg_mid = ImageServer::LoadGraph("resource/Enemy/body2/body2_down.png");
		break;
	case 3:
		_cg_mid = ImageServer::LoadGraph("resource/Enemy/body2/body2_down.png");
		break;
	}
	switch (pattern.foot) {
	case 1:
		_cg_bot = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_down.png");
		break;
	case 2:
		_cg_bot = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_down.png");
		break;
	case 3:
		_cg_bot = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_down.png");
		break;
	}
}

void ServerMachineUI::Update() {
	_visible = _owner.GetValidFlag();
}

void ServerMachineUI::Render() {
	if (_visible) {


		int alpha = _owner.GetEnergy();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y), GetColor(0, 0, 0), 1);
		DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y), _cg, 1);

		DrawExtendGraph(static_cast<int>(_pos.x)-200,
			static_cast<int>(_pos.y) - 100,
			static_cast<int>(_pos.x) + 500,
			static_cast<int>(_pos.y) + 600,
			_cg_bot
			, 1);
		DrawExtendGraph(static_cast<int>(_pos.x) - 200,
			static_cast<int>(_pos.y) - 100,
			static_cast<int>(_pos.x) + 500,
			static_cast<int>(_pos.y) + 600,
			_cg_top2
			, 1);
		DrawExtendGraph(static_cast<int>(_pos.x) - 200,
			static_cast<int>(_pos.y) - 100,
			static_cast<int>(_pos.x) + 500,
			static_cast<int>(_pos.y) + 600,
			_cg_mid
			, 1);
		DrawExtendGraph(static_cast<int>(_pos.x) - 200,
			static_cast<int>(_pos.y) - 100,
			static_cast<int>(_pos.x) + 500,
			static_cast<int>(_pos.y) + 600,
			_cg_top
			, 1);





		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}