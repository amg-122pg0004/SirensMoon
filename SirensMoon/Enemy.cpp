#include "Enemy.h"

Enemy::Enemy(Game& game) :Actor{ game }, _speed{5}
{

};

void Update() {
	_pos=(_nextPos - _pos)
}

void Render() {

}