#pragma once

#include "Logable.h"

class ConcreteLogable : public Logable
{
public:
	ConcreteLogable(int str, int def, int agi) : str{str}, def{def}, agi{agi} {}

	std::string toString() const override
	{
		std::string s = "Str: ";
		s.append(std::to_string(str));
		s.append("Def: ");
		s.append(std::to_string(def));
		s.append("Agi: ");
		s.append(std::to_string(agi));
		return s;
	}

private:
	int str;
	int def;
	int agi;
};