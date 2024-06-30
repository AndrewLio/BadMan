#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class System : public IModule {
public:
	System();
	~System();
	int hookdelay = 0;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
