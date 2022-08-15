#include "DamageCut.h"
#include "Game.h"
#include "ModeGame.h"

DamageCut::DamageCut(Game& game, ModeBase& mode, Vector2 pos, Vector2 size)
	:UIBase(game, mode, pos, size), _lifetime{ 60 }, _startTime{ 0 }
{
	_cg = ImageServer::LoadGraph("resource/Damage/damage.png");
	_easing = Easing::GetMode("OutQuint");
}

void DamageCut::Update() {

	auto elapsed = _game.GetFrameCount() - _startTime; // �o�ߎ���
	auto start = 0;    // �J�n�l
	auto stop = 100;        // �I���l
	auto lifetime = 60 * 1; // ��������

	if (elapsed < lifetime) {
		// �����_���̃C�[�W���O�֐����g��
		_moveX = _easing(elapsed, start, stop, lifetime);
	}

	if (_visible) {
		--_lifetime;
	}
	if (_lifetime <= 0) {
		_visible = false;
		dynamic_cast<ModeGame&>(_mode).SetPauseGame(false);
	}
}

void DamageCut::Render() {
	if (_visible && _lifetime < 59) {
		DrawBox(0, 0, screen_W, _pos.y, GetColor(120, 20, 30), 1);
		DrawBox(0, _pos.y + _size.y, screen_W, screen_H, GetColor(120, 20, 30), 1);
		DrawExtendGraph(_pos.x - _moveX, _pos.y, _pos.x + _size.x - _moveX, _pos.y + _size.y, _cg, 0);
	}
}

void DamageCut::DamageEvent() {
	_visible = true;
	_lifetime = 60;

	_startTime = _game.GetFrameCount();
}
