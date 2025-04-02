#pragma once
#include <string>

class AbstractWindow {
	friend class Editor;

public:
	virtual void Open() = 0;
	virtual void Update() = 0;
	virtual void Close() = 0;

public:
	const unsigned& GetID();
	const unsigned& GetID() const;

	const std::string& GetWindowName();
	const std::string& GetWindowName() const;

protected:
	std::string myWindowName;
	unsigned myID;
	bool myIsOpen = true;

	bool myWasLastOpen = true;
};