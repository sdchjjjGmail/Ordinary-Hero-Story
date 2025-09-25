#pragma once
#include "Actor.h"

class ICanBattle
{
public:
	virtual void Attack(ICanBattle* InTarget, int InDamage) = 0;
	virtual void TakeDamage(int InDamage) = 0;
	virtual ~ICanBattle() {};
};