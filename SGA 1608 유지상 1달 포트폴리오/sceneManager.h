#pragma once

#include "singletonBase.h"

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

	gameNode* _currentScene;
	gameNode* _readyScene;

	mapSceneList _mSceneList;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	gameNode* addScene(string sceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);

	sceneManager();
	~sceneManager();
};

