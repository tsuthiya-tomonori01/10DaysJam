#pragma once
#include "Iscene.h"

#include "KamataEngine.h"
#include "Novice.h"

#include "audio/Audio.h"

class GameOver : public Iscene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

	~GameOver();

private:


};

