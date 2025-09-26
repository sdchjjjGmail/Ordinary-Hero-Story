#pragma once
#include <string>

class Artifact
{
public:
	Artifact(std::string InName, int InLevel) : Name(InName), Level(InLevel)
	{}

	std::string GetName() const
	{
		return Name;
	}
	int GetLevel() const
	{
		return Level;
	}

	void SetLevel(int InLevel)
	{
		Level = InLevel;
	}

private:
	std::string Name;
	int Level;
};

