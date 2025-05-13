#pragma once

#include <string>
class Asset
{
public:
	virtual void Bind() { __noop; }
	virtual void Unbind() { __noop; }

	void SetID(const size_t& aID);
	const size_t& GetID() const;

	const std::string& GetName() const;
	void SetName(const std::string& aName);

private:
	std::string myName;
	size_t myID;
};