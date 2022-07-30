#include "Parser.h"

Elite::Parser::Parser()
{
}

Elite::Parser::~Parser()
{
}

void Elite::Parser::ParseObject(std::vector<FPoint3>& vertexBuffer, std::vector<IPoint3>& indexBuffer, const std::string& fileName)
{
	std::string line;
	std::ifstream input{};
	input.open(fileName, std::ios::in | std::ios::binary);
	if (input.is_open())
	{
		while (!input.eof())
		{
			std::getline(input, line);
			if (line[0] == 'v')
			{
				std::stringstream ss(line);
				std::string v, x, y, z;
				std::getline(ss, v, ' ');
				std::getline(ss, v, ' ');
				std::getline(ss, x, ' ');
				std::getline(ss, y, ' ');
				std::getline(ss, z, '\r');
				FPoint3 vertex;
				vertex.x = std::stof(x);
				vertex.y = std::stof(y);
				vertex.z = std::stof(z);
				vertexBuffer.push_back(vertex);
			}
			else if (line[0] == 'f')
			{
				std::stringstream ss(line);
				std::string f, x, y, z;
				std::getline(ss, f, ' ');
				std::getline(ss, x, ' ');
				std::getline(ss, y, ' ');
				std::getline(ss, z, '\r');
				IPoint3 face;
				face.x = std::stoi(x);
				face.y = std::stoi(y);
				face.z = std::stoi(z);
				indexBuffer.push_back(face);
			}
		}
		input.close();
	}
}
