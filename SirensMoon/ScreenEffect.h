#pragma once
#include "UIBase.h"
#include "Math.h"
#include <memory>

class Game;
class ModeBase;
class InputManager;
class SplitWindow;
class ScreenEffect :public UIBase {
public:
	ScreenEffect(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size);
	Type GetType() { return Type::ScreenEffect; }
    // �C�[�W���O����
    virtual void Easing(int elapsed) = 0;
    virtual void Update()override;
    virtual void Render()override;
    virtual void SetEffect(int delayTime,int lifeTime);
protected:
    int _cg; // �S�ẴO���t�B�b�N�n���h��
    int _delayTime; // �x������
    int _startTime; // �J�n����
    int _lifeTime;  // ��������
    double _alpha;  // �A���t�@
};