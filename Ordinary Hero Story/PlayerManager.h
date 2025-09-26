#pragma once
#include "Weapon.h"
#include "Armor.h"
#include "Artifact.h"
#include "Player.h"
#include "Stats.h"
#include "ICanBattle.h"
#include "Monster.h"

class PlayerManager
{
public:
	PlayerManager() : CurrentPlayer(new Player()) {};
	void SetPlayerWearings();

	void SetWeapon(Weapon* InWeapon);
	void SetArmor(Armor* InArmor);
	void AddArtifact(Artifact InArtifact);
	void Attack(Monster* InTarget);

	//void SetPlayer(Player* InPlayer)
	//{
	//	CurrentPlayer = InPlayer;
	//}
	void SetPlayerStat(Stats InType, int InStat);
	void SetPlayerHitPoint();
	void SetPlayerAttackPoint();
	void SetPlayerDefencePoint();
	void SetPlayerSpeed();
	void SetPlayerCriticalChance();
	//void SetPlayerCriticalDamageRate();

	Player* GetCurrentPlayer()
	{
		return CurrentPlayer;
	}
	Weapon* GetWeapon();
	Armor* GetArmor();
	Artifact GetArtifact();

private:
	Player* CurrentPlayer;
};
