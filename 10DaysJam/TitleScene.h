#pragma once
#include "KamataEngine.h"
#include "Novice.h"

#include "Iscene.h"

class TitleScene : public Iscene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

	~TitleScene();

private:


};

