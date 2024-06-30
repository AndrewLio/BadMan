#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class ClientSpoofer : public IModule {
private:
	bool ipSpf = false;
	bool guidSpf = false;

public:
	virtual const char* getModuleName();
	virtual void onEnable();
	virtual void onTick(GameMode* gm);
	virtual void onDisable();

	std::string GetGUID();
	virtual void GetIP();

	ClientSpoofer();
};