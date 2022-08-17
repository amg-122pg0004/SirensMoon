#pragma once
//!
//! @file Effect.h
//!
//! @brief �G�t�F�N�g�p�N���X
//!
#include "Actor.h"
#include "Math.h"
#include <string>
#include <vector>

// �G�t�F�N�g�p�N���X
class Effect:public Actor {
public:
    Effect(Game& game,ModeGame& mode,const Vector2& pos, int startTime);
    Type GetType()override { return Type::Effect; }
    // �C�[�W���O����
    virtual void Easing(int elapsed) = 0;
    virtual void Update()override;
    virtual void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
    bool isDead() {
        return !_active;
    };

protected:
    int _animNo;  // ���݂̃O���t�B�b�N�n���h��
    std::vector<int> _cg; // �S�ẴO���t�B�b�N�n���h��
    int _delayTime; // �x������
    int _startTime; // �J�n����
    int _lifeTime;  // ��������
    bool _active;   // �L������
    double _alpha;  // �A���t�@
    double _angle;  // ��]�p�x
    double _zoom;   // �g�嗦
    int _blendMode; // DX�u�����h���[�h
};