#include "oscillator.h"
#include <cmath>

f32 Oscillator::Generate(f64 phase, f32 frequency){
	switch(waveform){
		case OscillatorWaveform::Sine:
			return std::sin(M_PI*2.0*(frequency + detune)*phase);

		default: break;
	}

	return 0.f;
}