#include "Screen_Fade.h"
#include "Easing.h"
#include "Game.h"
class SplitWindow;
Screen_Fade::Screen_Fade(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:ScreenEffect(game, mode, window, pos, size), _feedout{false}
{
    _color = GetColor(255, 255, 255);
    _UIPriority = 13;
}

void Screen_Fade::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
    if (_feedout){
        _alpha = (linear(elapsed, 255, 0, _lifeTime));
    }
    else {
        _alpha = (linear(elapsed, 0, 255, _lifeTime));
    }
    _alpha=Math::Clamp(_alpha,0.0,255.0);
}

void Screen_Fade::Render() {
    if (!_visible){
        return;
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
    SetDrawMode(DX_DRAWMODE_BILINEAR);
    int Wsize{ splitscreen_W };
    if (_fullscreen) {
        Wsize = screen_W;
    }
    DrawBox(static_cast<int>(_pos.x), static_cast<int>(_pos.y)
        , static_cast<int>(_pos.x + Wsize), static_cast<int>(_pos.y + screen_H), _color, 1);

    SetDrawMode(DX_DRAWMODE_NEAREST);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};

void Screen_Fade::SetEffect(int delayTime, int lifeTime, unsigned int color,bool feedout ,bool fullscreen) {
    ScreenEffect::SetEffect(delayTime, lifeTime);
    _color = color;
    _feedout = feedout;
    _fullscreen = fullscreen;
    if (_feedout) {
        _alpha = 255;
    }
    else {
        _alpha = 0;
    }
}