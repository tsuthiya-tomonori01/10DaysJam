#pragma once

enum SceneType {
	TITLE,
	STAGE,
	CLEAR,
	OVER,
};

class Iscene
{

protected:

	static int sceneNo;

public:

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~Iscene();

	int GetSceneNo() { return sceneNo; }
};

