#ifndef NOTESCHEDULER_H
#define NOTESCHEDULER_H

#include "common.h"
#include <vector>
#include <functional>

struct NoteInfo {
	f32 beginTime;
	f32 endTime; // Signals the begin of the release time for envelopes with sustain
	u8 note;
	u8 envFlags; // 0 is dead

	// held is only useful for envelopes that have a sustain.
	bool held() const {return endTime < beginTime;}
	bool dead() const {return envFlags == 0;}
};

enum class QuantisationSetting {
	None,
	Sixteenth,
	Triplet,
	Eighth,
	Quarter,
	Half,
	Whole,
};

struct NoteScheduler {
	QuantisationSetting quantisation;
	std::vector<NoteInfo> notes;
	f32 time = 0.0;

	void Update(f32 dt);

	// note is in semitones
	// 128 is A 220
	void NoteOn(u8, f32 = 0.0);
	void NoteOff(u8);
	void Clear();
	void SoftClear();

	void ForEachActive(std::function<void (NoteInfo&)>);
};

#endif