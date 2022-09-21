#include "Screen_Fade.h"
#include "Easing.h"
#include "Game.h"

Screen_Fade::Screen_Fade(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:ScreenEffect(game, mode, pos, size)
{
    _color = GetColor(255, 255, 255);
}

void Screen_Fade::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
    _alpha = (linear(elapsed, 0, 255, _lifeTime));
}

void Screen_Fade::Render() {
    if (!_visible){
        return;
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
    SetDrawMode(DX_DRAWMODE_BILINEAR);

    DrawBox(_pos.x,_pos.y,_pos.x+splitscreen_W, _pos.y+screen_H, _color,1);

    SetDrawMode(DX_DRAWMODE_NEAREST);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};

void Screen_Fade::SetEffect(int delayTime, int lifeTime, unsigned int color) {
    ScreenEffect::SetEffect(delayTime, lifeTime);
    _color = color;
    
}