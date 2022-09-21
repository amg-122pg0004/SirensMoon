#include "ScreenEffect.h"
#include "Game.h"


ScreenEffect::ScreenEffect(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,pos,size }
{
	_visible = false;
	_UIPriority = 9;
}

void ScreenEffect::Update() {
	if (!_visible)
	{
		return;
	}
    // 経過時間＝現在時刻－(開始時刻＋遅延時間)
    auto elapsed = _game.GetFrameCount() - (_startTime + _delayTime);
    if (elapsed < 0) {
        return; // ディレイ(遅延)中
    }
    if (elapsed < _lifeTime) {
        Easing(elapsed);  // イージング処理
        return;
    }
    if (_loop) {
        _startTime = _game.GetFrameCount();
        return;
    }
    _visible = false;
}

void ScreenEffect::Render() {

}

void ScreenEffect::SetEffect(int delayTime, int lifeTime){
    _visible = true;
    _delayTime = delayTime;
    _lifeTime = lifeTime;
    _startTime = _game.GetFrameCount();
}
