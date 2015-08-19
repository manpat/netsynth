#include "notescheduler.h"
#include <algorithm>
#include <cmath>

void NoteScheduler::Update(f32 ntime){
	time = ntime;

	auto end = notes.end();
	auto nend = std::remove_if(notes.begin(), end, [](const NoteInfo& n){
		return n.dead();
	});

	notes.erase(nend, end);
}

static f32 snap(f32 v, f32 amt = 1.0){
	return std::round(v / amt) * amt;
}

void NoteScheduler::NoteOn(u8 note){
	if(note == 0) throw "NoteOn signal for note 0 is invalid";
	f32 beginTime = time;

	switch(quantisation){
	case QuantisationSetting::Sixteenth:beginTime = snap(time, 4.0/16.0); break;
	case QuantisationSetting::Triplet: 	beginTime = snap(time, 4.0/12.0); break;
	case QuantisationSetting::Eighth: 	beginTime = snap(time, 4.0/ 8.0); break;
	case QuantisationSetting::Quarter: 	beginTime = snap(time, 4.0/ 4.0); break;
	case QuantisationSetting::Half: 	beginTime = snap(time, 4.0/ 2.0); break;
	case QuantisationSetting::Whole: 	beginTime = snap(time, 4.0/ 1.0); break;

	case QuantisationSetting::None:
	default: break;
	}

	notes.push_back(NoteInfo{beginTime, -1.0f, note, 0x3 /* Two envelopes */});
}

void NoteScheduler::NoteOff(u8 note){
	auto ninfo = std::find_if(notes.begin(), notes.end(), [note](const NoteInfo& info){ 
		// Will search for a note of the same value and that is held
		return info.note == note && info.held(); 
	});

	if(ninfo != notes.end()){
		ninfo->endTime = time;
	}
}

void NoteScheduler::Clear(){
	notes.clear();
}