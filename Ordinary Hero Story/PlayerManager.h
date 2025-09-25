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
	void CreatePlayer();

	void SetWeapon(Player* InPlayer, Weapon* InWeapon);
	void SetArmor(Player* InPlayer, Armor* InArmor);
	void AddArtifact(Player* InPlayer, Artifact InArtifact);
	void Attack(Player* InPlayer, Monster* InTarget);

	void SetPlayer(Player InPlayer)
	{
		CurrentPlayer = InPlayer;
	}
	void SetPlayerStat(Player* InPlayer, Stats InType, int InStat);
	void SetPlayerHitPoint(Player* InPlayer);
	void SetPlayerAttackPoint(Player* InPlayer);
	void SetPlayerDefencePoint(Player* InPlayer);
	void SetPlayerSpeed(Player* InPlayer);
	void SetPlayerCriticalChance(Player* InPlayer);
	void SetPlayerCriticalDamageRate(Player* InPlayer);

	Player* GetCurrentPlayer()
	{
		return &CurrentPlayer;
	}
	Weapon* GetWeapon(Player* InPlayer);
	Armor* GetArmor(Player* InPlayer);
	Artifact GetArtifact(Player* InPlayer);

private:
	Player CurrentPlayer;
};
