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
	for (_viItem = _vItem.begin(); _viItem != _vItem.end();)
	{
		//�������� �ѹ� �浹���� �ʾҴٸ� ������Ʈ �� ������������ �˻��մϴ�.
		if (!(*_viItem)->getItemCollision())
		{
			(*_viItem)->update();
			++_viItem;
		}
		//�������� �ѹ� �浹�ߴٸ� ������Ʈ�� ���� �ʰ� �����մϴ�.
		else
		{
			_viItem = _vItem.erase(_viItem);
		}
	}
}

void objectManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem)->getItemX() > -TILESIZE && (*_viItem)->getItemX() < WINSIZEX + TILESIZE &&
			(*_viItem)->getItemY() > -TILESIZE && (*_viItem)->getItemY() < WINSIZEY + TILESIZE)
		{
			(*_viItem)->render();
		}
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

void objectManager::setSavebell(int tileNum)
{
	item* _save;
	_save = new saveBell;
	_save->init(_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right / 2, _tileMap->getTiles()[tileNum].rc.bottom);
	_vItem.push_back(_save);
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
