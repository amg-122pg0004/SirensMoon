#include "ScreenEffect.h"
#include "Game.h"
class SplitWindow;

ScreenEffect::ScreenEffect(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size }
    ,_cg{-1}, _delayTime{0}, _startTime{0}, _lifeTime{0},_alpha{255}
{
	_visible = false;
	_UIPriority = 9;
}

void ScreenEffect::Update() {
    // 経過時間＝現在時刻－(開始時刻＋遅延時間)
    auto elapsed = _game.GetFrameCount() - (_startTime + _delayTime);
    if (elapsed < 0) {
        return; // ディレイ(遅延)中
    }
    else {
        _visible = true;
    }
    if (elapsed < _lifeTime) {
        Easing(elapsed);  // イージング処理
        return;
    }
    _dead = true;
}

void ScreenEffect::Render() {

}

void ScreenEffect::SetEffect(int delayTime, int lifeTime){
    if (delayTime <= 0) {
        _visible = true;
    }
    _delayTime = delayTime;
    _lifeTime = lifeTime;
    _startTime = _game.GetFrameCount();
}
