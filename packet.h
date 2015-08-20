#ifndef PACKET_H
#define PACKET_H

#pragma pack(push, 1)

class PacketNote {
private:
	char type = 0;
public:
	char degree;
	char octave;
	char state;
};

class PacketParamConfig {
public:
	char paramId;
	float value;
};

class PacketModeConfig {
	char modeId;
	char mode;
};

class PacketScale {
private:
	char type = 1;
public:
	enum scaleType
	{
		AMinor,
		AMajor,
		Pentatonic
	};
	char rootNote;
};

#pragma pack(pop)

#endif//PACKET_H