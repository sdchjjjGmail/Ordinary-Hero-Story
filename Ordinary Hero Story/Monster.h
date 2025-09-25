#pragma once
#include <string>
#include "Actor.h"
#include "ICanBattle.h"

class Monster : public Actor, public ICanBattle
{
public:
	Monster() = default;
	Monster(std::string InName, int InLevel, int InDropGold) 
		: Name(InName), Level(InLevel), DropGold(InDropGold) {};
	virtual ~Monster() {};

	virtual void Attack(ICanBattle* InTarget, int InDamage) override;
	virtual void TakeDamage(int InDamage) override;

	std::string GetName() const
	{
		return Name;
	}
	int GetLevel() const
	{
		return Level;
	}
	int GetDropGold() const
	{
		return DropGold;
	}

	int GetDropExp() const
	{
		return DropExp;
	}

	void SetDropExp(int InDropExp)
	{
		DropExp = InDropExp;
	}
private:
	static constexpr int BasicDopExp = 100;

	std::string Name;
	int Level;
	int DropGold;
	int DropExp = BasicDopExp;
};
