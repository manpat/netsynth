#include "notescheduler.h"
#include "moc_serverlogic.h"
#include <algorithm>
#include <cmath>

void NoteScheduler::Update(f32 t){
	time = t * ServerLogic::tempo / 60.0;

	auto end = notes.end();
	auto nend = std::remove_if(notes.begin(), end, [](const NoteInfo& n){
		return n.dead();
	});

	notes.erase(nend, end);
}

static f32 snap(f32 v, f32 amt = 1.0){
	return std::ceil(v / amt) * amt;
}

void NoteScheduler::NoteOn(u8 note, f32 offset){
	if(note == 0) throw "NoteOn signal for note 0 is invalid";
	f32 begin = time + offset;

	switch(quantisation){
	case QuantisationSetting::Sixteenth:begin = snap(begin, 4.0/16.0); break;
	case QuantisationSetting::Triplet: 	begin = snap(begin, 4.0/12.0); break;
	case QuantisationSetting::Eighth: 	begin = snap(begin, 4.0/ 8.0); break;
	case QuantisationSetting::Quarter: 	begin = snap(begin, 4.0/ 4.0); break;
	case QuantisationSetting::Half: 	begin = snap(begin, 4.0/ 2.0); break;
	case QuantisationSetting::Whole: 	begin = snap(begin, 4.0/ 1.0); break;

	case QuantisationSetting::None:
	default: break;
	}

	notes.push_back(NoteInfo{begin, -1.0f, note, 0x3 /* Two envelopes */});
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

void NoteScheduler::ForEachActive(std::function<void (NoteInfo&)> func){
	for(auto& ni: notes){
		if(ni.beginTime > time) continue;
		if(ni.dead()) continue;

		func(ni);
	}
}
