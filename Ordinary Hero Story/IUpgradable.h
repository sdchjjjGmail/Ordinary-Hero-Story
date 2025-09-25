#pragma once
class IUpgradable
{
public:
	virtual ~IUpgradable() {};
	virtual IUpgradable* Upgrade() = 0;
};