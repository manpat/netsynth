#include "serverlogic.h"
#include "instrumentmanager.h"
#include "instrument.h"

ServerLogic::ServerLogic(){
	setWindowTitle("Server");
	resize(800, 600);
	show();

	fmodManager.start();
	instrumentManager = new InstrumentManager{&fmodManager, {}};
	while(!fmodManager.isRunning()) {}

	auto inst = instrumentManager->NewInstrument(1);

	inst->oscillators[0].waveform = OscillatorWaveform::Saw;
	inst->oscillators[0].detune = 0.0;

	inst->oscillators[1].waveform = OscillatorWaveform::Saw;
	inst->oscillators[1].pulsewidth = 0.2;
	inst->oscillators[1].detune = 0.6;

	inst->envelopes[0].type = EnvelopeType::AR;
	inst->envelopes[0].attack = 0.2;
	inst->envelopes[0].release = 2.0;

	inst->envelopes[1].type = EnvelopeType::Linear;
	inst->envelopes[1].attack = 0.5;
	inst->envelopes[1].release = 4.0;

	std::cout << "Instrument created" << std::endl;
}

ServerLogic::~ServerLogic(){
	fmodManager.kill();
	fmodManager.wait(2000); // Wait max 2s
	fmodManager.terminate(); // Just in case
}
