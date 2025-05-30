#pragma once

#include <vector>
#include <string>

#include "Submodel.h"

class Model
{
public:
	void SetMesh(const std::string& aMeshPath);

private:
	std::vector<Submodel> mySubmodels;

};