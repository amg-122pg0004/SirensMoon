#include "FX_Boom.h"
#include "Easing.h"


FX_Boom::FX_Boom(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game,mode,pos,startTime)
{
	//_cg.resize(120);
	//ImageServer::LoadDivGraph("resource/Effect/boom.png", 120, 8, 15 , 512, 512, _cg.data());

	_cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/boom2.png", 112, 8, 14, 512, 512, _cg.data());

	_zoom = 0.5;
	_lifeTime = 60*1;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_Boom::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime );

}

FX_Boom2::FX_Boom2(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	//_cg.resize(120);
	//ImageServer::LoadDivGraph("resource/Effect/boom.png", 120, 8, 15 , 512, 512, _cg.data());

	_cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/boom2.png", 112, 8, 14, 512, 512, _cg.data());

	_zoom = 2.5;
	_lifeTime = 60 * 1;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_Boom2::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);

}

