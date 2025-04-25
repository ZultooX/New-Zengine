#pragma once

#include <string>

class Submodel
{
public:
	Submodel(const int& aIdx, const std::string& aName);

private:
	int myMeshIdx = -1;
	std::string myName = "";
	std::string myMaterial = "";
};