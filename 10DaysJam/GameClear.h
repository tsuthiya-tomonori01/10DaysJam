#pragma once
#include "KamataEngine.h"
#include "Novice.h"

#include "Iscene.h"

class GameClear : public Iscene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

	~GameClear();
};

