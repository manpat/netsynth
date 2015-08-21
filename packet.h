#ifndef PACKET_H
#define PACKET_H

#include "common.h"
#include "typedefinitions.h"

#pragma pack(push, 1)

struct PacketNote : PacketType {
	s8 degree;
	s8 octave;
	u8 state;
};

struct PacketParamConfig : PacketType {
	f32 value;
};

struct PacketModeConfig : PacketType {
	u8 value;
};

struct PacketScale : PacketType {
	ScaleType scaleType;
	Notes rootNote;
};

#pragma pack(pop)

#endif//PACKET_H