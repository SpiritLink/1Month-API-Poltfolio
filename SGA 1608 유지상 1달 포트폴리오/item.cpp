#include "stdafx.h"
#include "item.h"


HRESULT item::init(float inputX, float inputY)
{
	x = inputX;
	y = inputY;
	collision = false;
	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
}

item::item()
{
}


item::~item()
{
}

HRESULT heart::init(float inputX, float inputY)
{
	x = inputX;
	y = inputY;
	frameCount = 0;
	_IMG = IMAGEMANAGER->addFrameImage("itemHeart", "IMAGE/item/itemHeart.bmp", 56, 24, 2, 1, true, RGB(255, 255, 255));
	itemType = ITEM_HEART;
	collision = false;
	return S_OK;
}

void heart::release()
{
}

void heart::update()
{
	itemRect = RectMakeCenter(x, y, _IMG->getFrameWidth(), _IMG->getFrameHeight());
}

void heart::render()
{
	//Rectangle(getMemDC(), itemRect.left, itemRect.top, itemRect.right, itemRect.bottom);
	_IMG->frameRender(getMemDC(), x - _IMG->getFrameWidth() / 2, y - _IMG->getFrameWidth() / 2, frameCount, 0);
}

heart::heart()
{
}

heart::~heart()
{
}

HRESULT shuriken::init(float inputX, float inputY)
{
	x = inputX;
	y = inputY;
	_IMG = IMAGEMANAGER->addImage("itemShuriken", "IMAGE/item/itemShuriken.bmp", 24, 24, true, RGB(255, 255, 255));
	itemType = ITEM_SHURIKEN;
	collision = false;
	return S_OK;
}

void shuriken::release()
{
}

void shuriken::update()
{
	itemRect = RectMakeCenter(x, y, _IMG->getWidth(), _IMG->getHeight());
}

void shuriken::render()
{
	//Rectangle(getMemDC(), itemRect.left, itemRect.top, itemRect.right, itemRect.bottom);
	_IMG->render(getMemDC(), x - _IMG->getWidth() / 2, y - _IMG->getHeight() / 2);
}

shuriken::shuriken()
{
}

shuriken::~shuriken()
{
}
