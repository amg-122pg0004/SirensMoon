#include "MiniMap.h"
#include "ImageServer.h"
#include "ModeGame.h"

MiniMap::MiniMap(Game& game, ModeBase& mode, Vector2 pos,Vector2 size) :UIBase{game,mode,pos,size}
{
	_cg_player = ImageServer::LoadGraph("resource/Map/test_map.jpg");
	_cg_map = ImageServer::LoadGraph("resource/Player/recon.png");
}

MiniMap::~MiniMap() {

}

void MiniMap::Update() {

}

void MiniMap::Render() {
	DrawExtendGraph(1050, 10,1750, 510,_cg_map, 0);

	Vector2 pos = { 12500,1400 };
	Vector2 pos2 = { 0,0 };
	//dynamic_cast<ModeGame&>(_mode).GetMapChips()->ReconRender(0, pos, pos2);

	//for (auto&& actor : _mode.GetObjects()) {
		//if (actor->GetType() == Actor::Type::Player) {
		//	DrawGraph(static_cast<int>(actor->GetPosition().x/10+1250),
	//			static)
	//	}
	//}
}
