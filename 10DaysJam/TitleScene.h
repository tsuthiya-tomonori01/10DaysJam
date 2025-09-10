#pragma once
#include "KamataEngine.h"
#include "Novice.h"

#include "Iscene.h"

#include "audio/Audio.h"

class TitleScene : public Iscene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

	~TitleScene();

private:

	uint32_t soundDataHandle_ = 0;

	uint32_t voiceHandle_ = 0;
};

