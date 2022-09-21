#include "ScreenEffect.h"
#include "Game.h"
class SplitWindow;

ScreenEffect::ScreenEffect(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size }
{
	_visible = true;
	_UIPriority = 9;
}

void ScreenEffect::Update() {
	if (!_visible)
	{
		return;
	}
    // �o�ߎ��ԁ����ݎ����|(�J�n�����{�x������)
    auto elapsed = _game.GetFrameCount() - (_startTime + _delayTime);
    if (elapsed < 0) {
        return; // �f�B���C(�x��)��
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
    _visible = true;
    _delayTime = delayTime;
    _lifeTime = lifeTime;
    _startTime = _game.GetFrameCount();
}
