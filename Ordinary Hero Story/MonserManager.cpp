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
        "ÃÊ¿ø ´Á´ë",
        GnerateLevel(InPlayer->GetLevel(), InPlayer->GetLevel() + 1),
        GnerateDropGold(InPlayer->GetLevel() * 10, InPlayer->GetLevel() * 30)
    );
    CreatedMonster->SetHitPoint(CreatedMonster->GetHitPoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetAttackPoint(CreatedMonster->GetAttackPoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
    CreatedMonster->SetDefencePoint(CreatedMonster->GetDefencePoint() + CreatedMonster->GetLevel() * CreatedMonster->GetStatValue());
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
