#include "MiniMap.h"
#include "ImageServer.h"
#include "ModeGame.h"

MiniMap::MiniMap(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size }, _visible{ false }
{
	_cg_map = ImageServer::LoadGraph("resource/Map/map_frame.png");
	_cg_player = ImageServer::LoadGraph("resource/Player/recon.png");
	_cg_enemy = ImageServer::LoadGraph("resource/enemy/recon.png");

	_inputManager = _game.GetInputManager();
}

MiniMap::~MiniMap() {

}

void MiniMap::Update() {

	if (_inputManager->CheckInput("ACTION", 'h', 0)) {
		_visible =true;
	}
	else {
		_visible = true;
	}
}

void MiniMap::Render() {

	if (_visible) {
		DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
			static_cast<int>(_pos.x + _size.x),static_cast<int>(_pos.y + _size.y), _cg_map, 0);

		Vector2 pos = { 1290,103 };
		Vector2 pos2 = { 0,0 };

		dynamic_cast<ModeGame&>(_mode).GetMapChips()->ReconRender(0, pos, pos2);
		
		float scale = 410.0 / 3240.0 * 0.97;
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Actor::Type::Player) {
				DrawGraph(static_cast<int>(actor->GetPosition().x * scale + pos.x),
					static_cast<int>(actor->GetPosition().y * scale + pos.y),
					_cg_player, 1);
			}
			
			if (actor->GetType() == Actor::Type::Enemy) {
					DrawGraph(static_cast<int>(actor->GetPosition().x * scale + pos.x),
						static_cast<int>(actor->GetPosition().y * scale + pos.y),
						_cg_enemy, 1);
			}
			
		}
	}
}
