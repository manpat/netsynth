#include "moc_serverlogic.h"
#include "instrumentmanager.h"
#include "instrument.h"
#include "notescheduler.h"

Scale ServerLogic::scale;
f32 ServerLogic::tempo = 60.0;

ServerLogic::ServerLogic(){
	setWindowTitle("Server");
	resize(800, 600);
	show();

	fmodManager.start();
	instrumentManager = new InstrumentManager{&fmodManager, {}};
	scale.ConstructScale(Notes::A, ScaleType::Major);

	connect(&fmodManager, SIGNAL(ready()), this, SLOT(fmodready()));
}

ServerLogic::~ServerLogic(){
	fmodManager.kill();
	fmodManager.wait(2000); // Wait max 2s
	fmodManager.terminate(); // Just in case
}

void ServerLogic::fmodready(){
	auto inst = instrumentManager->NewInstrument(1);

	inst->scheduler->quantisation = QuantisationSetting::Eighth;
	inst->scheduler->NoteOn(scale.GetNote(0, -1));
	inst->scheduler->NoteOn(scale.GetNote(2, -1), 0.5);
	inst->scheduler->NoteOn(scale.GetNote(4, -1), 1.0);
	inst->scheduler->NoteOn(scale.GetNote(7, -1), 1.5);

	inst->oscillators[0].waveform = OscillatorWaveform::Square;
	inst->oscillators[0].pulsewidth = 0.2;
	inst->oscillators[0].detune = 0.0;

	inst->oscillators[1].waveform = OscillatorWaveform::Sine;
	inst->oscillators[1].detune = 0.6;

	inst->envelopes[0].type = EnvelopeType::AR;
	inst->envelopes[0].attack = 0.7;
	inst->envelopes[0].decay = 0.5;
	inst->envelopes[0].sustain = 0.7;
	inst->envelopes[0].release = 1.0;

	inst->envelopes[1].type = EnvelopeType::AR;
	inst->envelopes[1].attack = 0.2;
	inst->envelopes[1].release = 1.0;

	std::cout << "Instrument created" << std::endl;
}