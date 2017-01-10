#include "stdafx.h"
#include "actionManager.h"
#include "action.h"

actionManager::actionManager()
{
}


actionManager::~actionManager()
{
}

HRESULT actionManager::init()
{
	return S_OK;
}

void actionManager::release()
{
	for (_viAction = _vAction.begin(); _viAction != _vAction.end();)
	{
		if (_vAction.size() != 0)
		{
			SAFE_DELETE(*_viAction);
			_viAction = _vAction.erase(_viAction);
		}
		else ++_viAction;
	}

	_vAction.clear();

}

void actionManager::update()
{
	for (int i = 0; i < _vAction.size();)
	{
		_vAction[i]->update();
		if (!(_vAction[i]->getIsMoving()))
		{
			SAFE_DELETE(_vAction[i]);
			_vAction.erase(_vAction.begin() + i);
		}
		else ++i;
	}
}

void actionManager::moveTo(image * img, float endX, float endY, float time)
{
	action* moveAction;
	moveAction = new action;
	moveAction->init();
	moveAction->moveTo(img, endX, endY, time);
	_vAction.push_back(moveAction);
}

void actionManager::moveTo(image * img, float endX, float endY, float time, void * cbFunction)
{
	action* moveAction;
	moveAction = new action;
	moveAction->init();
	moveAction->moveTo(img, endX, endY, time, (CALLBACKFUNCTION)cbFunction);
	_vAction.push_back(moveAction);

}


