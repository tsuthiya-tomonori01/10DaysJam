#pragma once
#include "KamataEngine.h"

#include "Novice.h"

class Enemy
{
public:

	//エネミ初期化関数
	void Initialize(KamataEngine::Vector2 Pos);

	//エネミ更新関数
	void Update();

	//エネミ描画関数
	void Draw(int x);

	//エネミーリセット
	void Reset(KamataEngine::Vector2 Pos);

	void SetisEnemyAlive(bool flag) {
		EnemyAlive = flag;
	};

	bool GetisEnemyAlive() {
		return EnemyAlive;
	};

	KamataEngine::Vector2 GetPosition() { return enemyPos; }
	float GetRad() { return enemyRad; }

private:

	//エネミー死亡フラグ
	bool EnemyAlive = true;

	//エネミー初期位置
	KamataEngine::Vector2 enemyPos;

	//エネミー大きさ
	float enemyRad;

	//エネミー画像
	int EG;

};

