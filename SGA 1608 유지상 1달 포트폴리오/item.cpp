#include "stdafx.h"
#include "item.h"


HRESULT item::init(float inputX, float inputY)
{
	x = inputX;
	y = inputY;
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
	return S_OK;
}

void heart::release()
{
}

void heart::update()
{
}

void heart::render()
{
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
	return S_OK;
}

void shuriken::release()
{
}

void shuriken::update()
{
}

void shuriken::render()
{
}

shuriken::shuriken()
{
}

shuriken::~shuriken()
{
}
