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
    // �o�ߎ��ԁ����ݎ����|(�J�n�����{�x������)
    auto elapsed = _game.GetFrameCount() - (_startTime + _delayTime);
    if (elapsed < 0) {
        return; // �f�B���C(�x��)��
    }
    else {
        _visible = true;
    }
    if (elapsed < _lifeTime) {
        Easing(elapsed);  // �C�[�W���O����
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
