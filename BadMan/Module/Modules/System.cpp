#include "System.h"

System::System() : IModule(0, Category::SYSTEM, "Systems to prevent crashes") {

}

System::~System() {
}

const char* System::getModuleName() {
	return ("System");
}

void System::onTick(GameMode* gm) {

}
