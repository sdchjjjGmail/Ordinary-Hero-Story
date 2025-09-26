#pragma once
#include "Item.h"

class Potion
{
public:
	Potion()
	{
		PotionLevel = 1;
		Price = 30;
		HealAmount = 30;
	};
	int GetPotionLevel() const
	{
		return PotionLevel;
	}
	int GetPrice() const 
	{
		return Price;
	}
	int GetHealAmount() const
	{
		return HealAmount;
	}

	void SetPotionLevel(int InLevel)
	{
		PotionLevel = InLevel;
		SetPrice();
		SetHealAmount();
	}

private:
	static constexpr int PriceIncrease = 10;
	static constexpr int HealIncrease = 20;

	void SetPrice()
	{
		Price += PriceIncrease * PotionLevel;
	}
	void SetHealAmount()
	{
		HealAmount += HealIncrease * PotionLevel;
	}

	int PotionLevel;
	int Price;
	int HealAmount;
};

