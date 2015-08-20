#ifndef PACKET_H
#define PACKET_H

#pragma pack(push, 1)

#include "common.h"

class PacketNote {
private:
	u8 type = 0;
public:
	s8 degree;
	s8 octave;
	u8 state;
};

class PacketParamConfig {
public:
	u8 paramId;
	float value;
};

class PacketModeConfig {
	u8 modeId;
	u8 mode;
};

class PacketScale {
private:
	u8 type = 1;
public:
	enum ScaleType : u8 {
		Minor,
		Major,
		Pentatonic
	};

	ScaleType scaleType;
	s8 rootNote;
};

#pragma pack(pop)

#endif//PACKET_H