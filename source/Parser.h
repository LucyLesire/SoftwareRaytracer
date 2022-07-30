#pragma once
#include "EMath.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>

namespace Elite
{
	class Parser
	{
	public:
		Parser();
		~Parser();

		void ParseObject(std::vector<FPoint3>& vertexBuffer, std::vector<IPoint3>& indexBuffer, const std::string& fileName);
	};
}


