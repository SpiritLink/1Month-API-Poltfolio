#include "stdafx.h"
#include "objectManager.h"


HRESULT objectManager::init()
{
	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update()
{
}

void objectManager::render()
{
}

void objectManager::setHeart(float x, float y)
{
	item* _item;
	_item = new heart;
	_item->init(x, y);
	_vItem.push_back(_item);
}

void objectManager::setShuriken(float x, float y)
{
	item* _item;
	_item = new shuriken;
	_item->init(x, y);
	_vItem.push_back(_item);
}

void objectManager::addItemX(int value)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->addItemX(value);
	}
}

void objectManager::addItemY(int value)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->addItemY(value);
	}
}

objectManager::objectManager()
{
}


objectManager::~objectManager()
{
}
