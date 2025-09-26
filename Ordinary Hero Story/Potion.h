#pragma once

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
	static constexpr int PriceIncrease = 3;
	static constexpr int HealIncrease = 15;

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

