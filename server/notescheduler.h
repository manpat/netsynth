#ifndef NOTESCHEDULER_H
#define NOTESCHEDULER_H

#include "common.h"
#include <vector>

struct NoteInfo {
	f32 beginTime;
	f32 endTime; // Signals the begin of the release time for envelopes with sustain
	u8 note; // note 0 is dead

	// held is only useful for envelopes that have a sustain.
	bool held() const {return endTime < beginTime;}
	bool dead() const {return note == 0;}
};

enum class QuantisationSetting {
	None,
	Sixteenth,
	Eighth,
	Triplet,
	Quarter,
	Half,
	Whole,
};

struct NoteScheduler {
	QuantisationSetting quantisation;
	std::vector<NoteInfo> notes;
	f32 time;

	void Update(f32 time);

	void NoteOn(u8);
	void NoteOff(u8);
	void Clear();
};

#endif