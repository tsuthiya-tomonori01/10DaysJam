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
		Novice::DrawSprite(int(enemyPos.x) - x, int(enemyPos.y),EnemyPng,1.0,1.0, 0.0f, WHITE);
	}
}

void Enemy::Reset(Vector2 Pos) {

	enemyPos = Pos;
}