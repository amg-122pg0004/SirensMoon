#pragma once
#include "Player.h"

class PlayerA :public Player {
public:
	PlayerA(Game& game, ModeGame& base, int playernum);
	Actor::Type GetType() override { return Actor::Type::PlayerA; }
	/*画像をロードする*/
	void Load();

	/*銃を撃つ*/
	void Action() override;

	/**
	 * @brief 発射する弾種を返す
	 * 
	 * \return GreenBulletが準備されていればTrue
	 */
	bool GetBulletType() { return _setGreenBullet; }

	void AnimUpdate()override;

	int GetAmmo() { return _bullet; }
	int GetCharge() { return _charge; }
	void TakeAmmo();
private:
	bool _setGreenBullet;

	/*射撃関係*/
	int _bullet;//残りの弾数
	int _charge;//チャージ
	int _cooldown;//クールダウン
};