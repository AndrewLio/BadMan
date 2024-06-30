#pragma once

#include "Module.h"

class ServerRotations : public IModule {
private:
public:
	
	int test1 = 0;
	float test2 = 0.f;

	ServerRotations();
	~ServerRotations();

	virtual const char* getModuleName();
};