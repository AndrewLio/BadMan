#include "ServerRotations.h"

ServerRotations::ServerRotations() : IModule(0, Category::VISUAL, "Server Rotations") {
	registerIntSetting("1 (Int)", &test1, test1, 0, 60);
	registerFloatSetting("2 (Float)", &test2, test2, 0, 60);
}

ServerRotations::~ServerRotations() {
}

const char* ServerRotations::getModuleName() {
	return "ServerRotations";
}