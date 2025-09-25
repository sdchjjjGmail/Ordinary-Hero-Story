#pragma once
#include <vector>
#include "Actor.h"
#include "ICanBattle.h"
#include "Weapon.h"
#include "Armor.h"
#include "Artifact.h"

class Player : public Actor, public ICanBattle
{
public:
	Player() = default;
	Player(int InLevel, int InMyGold)
	{
		Level = InLevel;
		MyGold = InMyGold;
		ExPoint = 0;
		AvailableStat = 0;
		RequiredExpForLvUp = 100;
	};
	virtual ~Player() {};

	virtual void Attack(ICanBattle* InTarget, int InDamage) override;
	virtual void TakeDamage(int InDamage) override;

	int GetLevel() const
	{
		return Level;
	}
	int GetExp() const
	{
		return ExPoint;
	}
	int GetRequiredExpForLvUp() const
	{
		return RequiredExpForLvUp;
	}
	int GetAvailableStat() const
	{
		return AvailableStat;
	}
	int GetMyGold() const
	{
		return MyGold;
	}
	Weapon* GetPlayerWeapon()
	{
		return &PlayerWeapon;
	}
	Armor* GetPlayerArmor()
	{
		return &PlayerArmor;
	}
	std::vector<Artifact> GetArtifactList()
	{
		return ArtifactList;
	}

	void SetLevel(int InLevel)
	{
		Level = InLevel;
	}
	void SetExPoint(int InPoint)
	{
		ExPoint += InPoint;
		if (ExPoint >= RequiredExpForLvUp)
		{
			SetLevel(Level++);
			SetRequiredExpForLvUp();
			SetAvailableStat(GetStatValue());
		}
	}
	void SetRequiredExpForLvUp()
	{
		RequiredExpForLvUp += Level * 100;
	}
	void SetAvailableStat(int InStat)
	{
		AvailableStat += InStat;
	}
	void SetMyGold(int InMyGold)
	{
		MyGold = InMyGold;
	}
	void SetPlayerWeapon(Weapon* InWeapon)
	{
		PlayerWeapon = *InWeapon;
	}
	void SetPlayerArmor(Armor* InArmor)
	{
		PlayerArmor = *InArmor;
	}
	void AddPlayerArtifact(Artifact* InArtifact)
	{
		ArtifactList.push_back(*InArtifact);
	}

private:
	int Level;
	int ExPoint;
	int RequiredExpForLvUp;
	int AvailableStat;
	int MyGold;
	Weapon PlayerWeapon;
	Armor PlayerArmor;
	std::vector<Artifact> ArtifactList;
};
