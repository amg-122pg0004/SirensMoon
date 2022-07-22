#include "ServerMachineUI.h"
#include "Game.h"
#include "ImageServer.h"
#include "ServerMachine.h"

ServerMachineUI::ServerMachineUI(Game& game, ModeBase& mode, Vector2 pos, Vector2 size, ServerMachine& owner)
	:UIBase{game,mode,pos,size},_visible{false},_owner{owner}
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/Map/map_frame.png");
}

void ServerMachineUI::Update() {
	_visible = _owner.GetValidFlag();
}

void ServerMachineUI::Render() {
	if (_visible) {
		DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y), _cg, 0);
	}
}