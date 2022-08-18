//!
//! @file Effect.cpp
//!
//! @brief �G�t�F�N�g�p�N���X
//!
#include "Effect.h"
#include "Easing.h"
#include "DxLib.h"
#include "Game.h"

// �R���X�g���N�^
Effect::Effect(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
    :Actor(game,mode)
    ,_animNo{ 0 }
    , _delayTime{ 0 }
    , _startTime{ startTime }
    , _lifeTime{ 0 }
    , _active{ true }
    , _alpha{ 255 }
    , _angle{ 0 }
    , _zoom{ 1 }
    , _blendMode{ DX_BLENDMODE_ADD }
    ,_loop{false}
{
    _pos = pos;
    _renderPriority = 100000;
}
// �X�V
void Effect::Update() {
    _renderPriority = _pos.y;
    if (!_active) {
        _dead = true;
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
    if(_loop) {
        _startTime = _game.GetFrameCount();
        return;
    }
    _active = false;
}
// �`��
void Effect::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
    SetDrawBlendMode(_blendMode, static_cast<int>(_alpha));
    SetDrawMode(DX_DRAWMODE_BILINEAR);

    int x = static_cast<int>(_pos.x-camera_pos.x+window_pos.x);
    int y = static_cast<int>(_pos.y-camera_pos.y+window_pos.y);

    DrawRotaGraph(x, y, _zoom, _angle, _cg[_animNo], true, false);

    SetDrawMode(DX_DRAWMODE_NEAREST);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}