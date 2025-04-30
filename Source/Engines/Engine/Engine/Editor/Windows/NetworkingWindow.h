#pragma once

#include "Window.h"


class NetworkingWindow final : public AbstractWindow {

public:
	NetworkingWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;

private:
	bool myIsConnected = false;

	void ConnectToServer();
	void DisconnectToServer();
};