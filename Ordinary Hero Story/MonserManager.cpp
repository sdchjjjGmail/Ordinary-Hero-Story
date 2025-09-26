#include "MonsterManager.h"
#include <random>
#include <string>

Monster* MonsterManager::CreateMonster(Player InPlayer, Field InCurrentField)
{
    switch (InCurrentField)
    {
    case Field::Field1:
        return CreateField1Monster(&InPlayer);
        break;
    default:
        break;
    }

    return new Monster();
}

Monster* MonsterManager::CreateField1Monster(Player* InPlayer)
{
    Monster* CreatedMonster = new Monster(
        "초원 늑대",
        GnerateLevel(InPlayer->GetLevel(), InPlayer->GetLevel() + 1),
        GnerateDropGold(InPlayer->GetLevel() * 10, InPlayer->GetLevel() * 30)
    );
    CreatedMonster->SetHitPoint(CreatedMonster->GetHitPoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetAttackPoint(CreatedMonster->GetAttackPoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetDefencePoint(CreatedMonster->GetDefencePoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    // 초원 늑대의 특성은 빠른 속도
    CreatedMonster->SetSpeed(CreatedMonster->GetSpeed() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue() + 10);
    CreatedMonster->SetDropExp(CreatedMonster->GetLevel() * 50);
    return CreatedMonster;
}

Monster* MonsterManager::CreateField2Monster(Player* InPlayer)
{
    Monster* CreatedMonster = new Monster(
        "숲 고블린",
        GnerateLevel(InPlayer->GetLevel(), InPlayer->GetLevel() + 1),
        GnerateDropGold(InPlayer->GetLevel() * 10, InPlayer->GetLevel() * 30)
    );
    CreatedMonster->SetHitPoint(CreatedMonster->GetHitPoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetAttackPoint(CreatedMonster->GetAttackPoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetDefencePoint(CreatedMonster->GetDefencePoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetSpeed(CreatedMonster->GetSpeed() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    // 숲 고블린의 특성은 높은 크리티컬 확률과 드랍 골드
    CreatedMonster->SetCriticalChance(CreatedMonster->GetCriticalChance() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue() + 15);
    CreatedMonster->SetDropExp(CreatedMonster->GetLevel() * 100);
    return CreatedMonster;
}

Monster* MonsterManager::CreateField3Monster(Player* InPlayer)
{
    Monster* CreatedMonster = new Monster(
        "늪 리자드맨",
        GnerateLevel(InPlayer->GetLevel(), InPlayer->GetLevel() + 1),
        GnerateDropGold(InPlayer->GetLevel() * 10, InPlayer->GetLevel() * 30)
    );
    // 늪 리자드맨의 특성은 높은 체력
    CreatedMonster->SetHitPoint(CreatedMonster->GetHitPoint() + CreatedMonster->GetLevel() * (CreatedMonster->GetStatValue() + 3));
    CreatedMonster->SetAttackPoint(CreatedMonster->GetAttackPoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetDefencePoint(CreatedMonster->GetDefencePoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetSpeed(CreatedMonster->GetSpeed() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetDropExp(CreatedMonster->GetLevel() * 50);
    return CreatedMonster;
}

int MonsterManager::GnerateLevel(int InMin, int InMax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(InMin, InMax);
    return dist(gen);
}

int MonsterManager::GnerateDropGold(int InMin, int InMax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(InMin, InMax);
    return dist(gen);
}

int MonsterManager::GnerateDropExp(int InMin, int InMax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(InMin, InMax);
    return dist(gen);
}
