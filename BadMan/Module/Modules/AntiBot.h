#pragma once

#include "Module.h"

class AntiBot : public IModule {
private:
	bool hitboxCheck = true;
	bool nameCheck = false;
	bool nameCheckA = false;
	bool invisibleCheck = true;
	bool entityIdCheck = true;
	bool otherCheck = true;
	bool extraCheck = true;
	bool playerCheck = true;

public:
	SettingEnum mode = this;
	AntiBot();
	~AntiBot();

	inline bool isHitboxCheckEnabled() {
		return hitboxCheck && isEnabled();
	}
	inline bool isASCIICheckEnabled() {
		return nameCheck && isEnabled();
	}
	inline bool isNameCheckEnabled() {
		return nameCheckA && isEnabled();
	}
	inline bool isInvisibleCheckEnabled() {
		return invisibleCheck && isEnabled();
	}
	inline bool isEntityIdCheckEnabled() {
		return entityIdCheck && isEnabled();
	}
	inline bool isOtherCheckEnabled() {
		return otherCheck && isEnabled();
	}
	inline bool isExtraCheckEnabled() {
		return extraCheck && isEnabled();
	}
	inline bool isPlayerCheckEnabled() {
		return playerCheck && isEnabled();
	}
	// Inherited via IModule
	virtual const char* getModuleName() override;
};
