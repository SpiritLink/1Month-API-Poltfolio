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
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->update();
	}
}

void objectManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		//좌표가 화면의 안에 있다면 (여유공간은 TILESIZE만큼)
		//if ((*_viItem)->getItemX() > -TILESIZE && (*_viItem)->getItemX() < WINSIZEX + TILESIZE &&
		//	(*_viItem)->getItemY() > -TILESIZE && (*_viItem)->getItemY() < WINSIZEY + TILESIZE)
		//{
			(*_viItem)->render();
		//}
	}
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
	vector<item*>::iterator _vItemi;
	for (_vItemi = _vItem.begin(); _vItemi != _vItem.end(); ++_vItemi)
	{
		(*_vItemi)->addItemX(value);
	}
}

void objectManager::addItemY(int value)
{
	vector<item*>::iterator _vItemi;
	for (_vItemi = _vItem.begin(); _vItemi != _vItem.end(); ++_vItemi)
	{
		(*_vItemi)->addItemY(value);
	}
}

objectManager::objectManager()
{
}


objectManager::~objectManager()
{
}
