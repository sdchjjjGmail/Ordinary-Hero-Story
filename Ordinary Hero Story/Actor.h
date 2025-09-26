#pragma once

class Actor
{
public:
	// ��� ĳ����(�÷��̾�/����)�� �ʱ⿡ ������ �ɷ�ġ�� �ʱ�ȭ.
	// ���� ���� ��ҵ�(����, ������ ��)�� ���� �ɷ�ġ�� ����ȭ�� �д�.
	Actor()
	{
		HitPointStat = 0;
		AttackPointStat = 0;
		DefencePointStat = 0;
		SpeedStat = 0;
		CriticalChanceStat = 0;
		CriticalDamageRate = 2;
	};

	int GetStatValue() const
	{
		return StatValue;
	}

	int GetHitPoint() const
	{
		return HitPoint;
	}
	int GetAttackPoint() const
	{
		return AttackPoint;
	}
	int GetDefencePoint() const
	{
		return DefencePoint;
	}
	int GetSpeed() const
	{
		return Speed;
	}
	int GetCriticalChance() const
	{
		return CriticalChance;
	}
	int GetCriticalDamageRate() const
	{
		return CriticalDamageRate;
	}

	int GetOrgHitPoint() const
	{
		return OrgHitPoint;
	}
	int GetOrgAttackPoint() const
	{
		return OrgAttackPoint;
	}
	int GetOrgDefencePoint() const
	{
		return OrgDefencePoint;
	}
	int GetOrgSpeed() const
	{
		return OrgSpeed;
	}
	int GetOrgCriticalChance() const
	{
		return OrgCriticalChance;
	}
	//int GetOrgCriticalDamageRate() const
	//{
	//	return OrgCriticalDamageRate;
	//}

	int GetHitPointStat() const
	{
		return HitPointStat;
	}
	int GetAttackPointStat() const
	{
		return AttackPointStat;
	}
	int GetDefencePointStat() const
	{
		return DefencePointStat;
	}
	int GetSpeedStat() const
	{
		return SpeedStat;
	}
	int GetCriticalChanceStat() const
	{
		return CriticalChanceStat;
	}
	//int GetCriticalDamageRateStat() const
	//{
	//	return CriticalDamageRateStat;
	//}
	
	void SetHitPoint(int InHitPoint)
	{
		HitPoint = InHitPoint;
	}
	void SetAttackPoint(int InAttackPoint)
	{
		AttackPoint = InAttackPoint;
	}
	void SetDefencePoint(int InDefencePoint)
	{
		DefencePoint = InDefencePoint;
	}
	void SetSpeed(int InSpeed)
	{
		Speed = InSpeed;
	}
	void SetCriticalChance(int InCriticalChance)
	{
		CriticalChance = InCriticalChance;
	}
	//void SetCriticalDamageRate(int InCriticalDamageRate)
	//{
	//	CriticalDamageRate = InCriticalDamageRate;
	//}

	void SetHitPointStat(int InStat)
	{
		HitPointStat = InStat;
	}
	void SetAttackPointStat(int InStat)
	{
		AttackPointStat = InStat;
	}
	void SetDefencePointStat(int InStat)
	{
		DefencePointStat = InStat;
	}
	void SetSpeedStat(int InStat)
	{
		SpeedStat = InStat;
	}
	void SetCriticalChanceStat(int InStat)
	{
		CriticalChanceStat = InStat;
	}
	//void SetCriticalDamageRateStat(int InStat)
	//{
	//	CriticalDamageRateStat = InStat;
	//}

private:
	static constexpr int StatValue = 5;
	static constexpr int OrgHitPoint = 100;
	static constexpr int OrgAttackPoint = 20;
	static constexpr int OrgDefencePoint = 10;
	static constexpr int OrgSpeed = 15;
	static constexpr int OrgCriticalChance = 15;
	static constexpr int OrgCriticalDamageRate = 2;

	int HitPointStat;
	int AttackPointStat;
	int DefencePointStat;
	int SpeedStat;
	int CriticalChanceStat;
	int CriticalDamageRateStat;

	int HitPoint = OrgHitPoint;
	int AttackPoint = OrgAttackPoint;
	int DefencePoint = OrgDefencePoint;
	int Speed = OrgSpeed;
	int CriticalChance = OrgCriticalChance;
	// ũ��Ƽ�� �������� 2��� ����
	int CriticalDamageRate = OrgCriticalDamageRate;
};