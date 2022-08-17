#pragma once
//!
//! @file Effect.h
//!
//! @brief エフェクト用クラス
//!
#include "Actor.h"
#include "Math.h"
#include <string>
#include <vector>

// エフェクト用クラス
class Effect:public Actor {
public:
    Effect(Game& game,ModeGame& mode,const Vector2& pos, int startTime);
    Type GetType()override { return Type::Effect; }
    // イージング処理
    virtual void Easing(int elapsed) = 0;
    virtual void Update()override;
    virtual void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
    bool isDead() {
        return !_active;
    };

protected:
    int _animNo;  // 現在のグラフィックハンドル
    std::vector<int> _cg; // 全てのグラフィックハンドル
    int _delayTime; // 遅延時間
    int _startTime; // 開始時間
    int _lifeTime;  // 生存時間
    bool _active;   // 有効無効
    double _alpha;  // アルファ
    double _angle;  // 回転角度
    double _zoom;   // 拡大率
    int _blendMode; // DXブレンドモード
};