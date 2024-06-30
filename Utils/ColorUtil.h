#pragma once
#include "../BadMan/DrawUtils.h"
#include "TimerUtil.h"

class ColorUtil {
private:
	unsigned __int64 lastMS = getCurrentMs();
	inline static unsigned __int64 getCurrentMs() {
		FILETIME f;
		GetSystemTimeAsFileTime(&f);
		(unsigned long long)f.dwHighDateTime;
		unsigned __int64 nano = ((unsigned __int64)f.dwHighDateTime << 32LL) + (unsigned __int64)f.dwLowDateTime;
		return (nano - 116444736000000000LL) / 10000;
	}

public:
	static MC_Color waveColor(int red, int green, int blue, int red2, int green2, int blue2, long index);
	static MC_Color RGBWave(int red, int green, int blue, int red2, int green2, int blue2, long index);
	static MC_Color rainbowColor(float seconds, float saturation, float brightness, long index);
	static MC_Color astolfoRainbow(int yOffset, int yTotal);
	static MC_Color interfaceColor(int index);
	static MC_Color waveColortwo(int red, int green, int blue, int red2, int green2, int blue2, long index);
	static MC_Color RGBWavetwo(int red, int green, int blue, int red2, int green2, int blue2, long index);
	static MC_Color rainbowColortwo(float seconds, float saturation, float brightness, long index);
	static MC_Color astolfoRainbowtwo(int yOffset, int yTotal);
	static MC_Color interfaceColortwo(int index);
	static MC_Color rainbowColorthree(float seconds, float saturation, float brightness, long index);
	inline static MC_Color getRainbowColor(float seconds, float saturation, float brightness, long index) {
		float currentHue = (((getCurrentMs() + index) % (int)(seconds * 1000)) / (float)(seconds * 1000));
		float red, green, blue = 0.0f;
		Utils::ColorConvertHSVtoRGB(currentHue, saturation, brightness, red, green, blue);

		return MC_Color(red, green, blue);
	}
};
