#include <cstdio>
#include "GameManager.h"

int main()
{
	GameManager* Manager 
		= new GameManager(PlayerManager(),MonsterManager(), UiManager(), MapManager());
	Manager->GameStart();
}