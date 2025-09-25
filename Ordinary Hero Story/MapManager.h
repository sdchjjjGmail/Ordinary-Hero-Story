#pragma once
#include "Player.h"
#include "Fields.h"

class MapManager
{
public:
	void SetCurrentMap(Field InField)
	{
		CurrentMap = InField;
	}

	Field GetCurrentMap() const
	{
		return CurrentMap;
	}

private:
	Field CurrentMap;
};
