#include "oscillator.h"
#include "common.h"
#include <cmath>

f32 Oscillator::Generate(f64 phase, f64 frequency){
	switch(waveform){
		case OscillatorWaveform::Sine:
			return std::sin(M_PI*2.0*(frequency * detune * octave)*phase);

		case OscillatorWaveform::Square:
			return (std::fmod(phase*(frequency * detune * octave), 1.0) < pulsewidth)?-1.0:1.0;

		case OscillatorWaveform::Saw:
			return fmod(phase*(frequency * detune * octave)*2.0, 2.0)-1.0;

		case OscillatorWaveform::Triangle:{
			auto nph = fmod(phase*(frequency * detune * octave), 1.0);
			if(nph <= 0.5) return (nph-0.25)*4.0;

			return (0.75-nph)*4.0;
		}

		case OscillatorWaveform::None:
		default: break;
	}

	return 0.f;
}