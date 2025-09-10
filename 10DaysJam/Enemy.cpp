#include "Enemy.h"

using namespace KamataEngine;

void Enemy::Initialize(Vector2 Pos) {

	enemyRad = 64.0f;
	Reset(Pos);

	EnemyAlive = true;
}

void Enemy::Update() {

}

void Enemy::Draw(int x) {

	if (EnemyAlive)
	{
		Novice::DrawBox(int(enemyPos.x) - x, int(enemyPos.y), int(enemyRad), int(enemyRad), 0.0f, BLUE, kFillModeSolid);
	}
}

void Enemy::Reset(Vector2 Pos) {

	enemyPos = Pos;
}