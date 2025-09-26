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
	Player()
	{
		Level = 1;
		MyGold = 50;
		ExPoint = 0;
		AvailableStat = 0;
		RequiredExpForLvUp = 100;
		FullHitPoint = 100;
		PotionCount = 0;
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
	int GetFullHitPoint() const
	{
		return FullHitPoint;
	}
	Armor* GetPlayerArmor()
	{
		return &PlayerArmor;
	}
	std::vector<Artifact> GetArtifactList()
	{
		return ArtifactList;
	}
	int GetPotionCount() const
	{
		return PotionCount;
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
			SetAvailableStat(GetStatValue());
		}
	}
	void SetRequiredExpForLvUp()
	{
		RequiredExpForLvUp += Level * 70;
	}
	void SetAvailableStat(int InStat)
	{
		AvailableStat += InStat;
	}
	void SetMyGold(int InMyGold)
	{
		MyGold = InMyGold;
	}
	void SetFullHitPoint(int InFullHitPoint)
	{
		FullHitPoint = InFullHitPoint;
	}
	void SetPotionCount(int InCount)
	{
		PotionCount = InCount;
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
	int FullHitPoint;
	int PotionCount;
	Weapon PlayerWeapon;
	Armor PlayerArmor;
	std::vector<Artifact> ArtifactList;
};
