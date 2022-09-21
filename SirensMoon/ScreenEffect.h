#pragma once
#include "UIBase.h"
#include "Math.h"
#include <memory>

class Game;
class ModeBase;
class InputManager;

class ScreenEffect :public UIBase {
public:
	ScreenEffect(Game& game, ModeBase& mode, Vector2 pos, Vector2 size);
	Type GetType() { return Type::ScreenEffect; }
    // イージング処理
    virtual void Easing(int elapsed) = 0;
    virtual void Update()override;
    virtual void Render()override;
    virtual void SetEffect(int delayTime,int lifeTime);
protected:
    int _animNo;  // 現在のグラフィックハンドル
    int _cg; // 全てのグラフィックハンドル
    int _delayTime; // 遅延時間
    int _startTime; // 開始時間
    int _lifeTime;  // 生存時間
    bool _active;   // 有効無効
    double _alpha;  // アルファ

    bool _loop;//trueにするとループ表示
};