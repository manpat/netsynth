#include "moc_serverlogic.h"
#include "instrumentmanager.h"
#include "instrument.h"
#include "notescheduler.h"
#include "packet.h"

Scale ServerLogic::scale;
f32 ServerLogic::tempo = 60.0;

ServerLogic::ServerLogic(){
	setWindowTitle("Server");
	resize(200, 200);
	show();

	serverNetwork = new ServerNetwork();

	fmodManager.start();
	instrumentManager = new InstrumentManager{&fmodManager, {}};
	scale.ConstructScale(Notes::A, ScaleType::Major);

	connect(&fmodManager, SIGNAL(ready()), this, SLOT(fmodready()));
	connect(serverNetwork, SIGNAL(DataReceived(QByteArray, u32)), this, SLOT(HandleData(QByteArray, u32)));
}

ServerLogic::~ServerLogic(){
	fmodManager.kill();
	fmodManager.wait(2000); // Wait max 2s
	fmodManager.terminate(); // Just in case
}

void ServerLogic::fmodready(){
	/*
	auto inst = instrumentManager->NewInstrument(1);

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
	*/
}

void ServerLogic::ClientConnected(u32 id) {
	instrumentManager->NewInstrument(id);
}

void ServerLogic::HandleData(QByteArray data, u32 id) {
	auto inst = instrumentManager->GetInstrument(id);

	auto type = reinterpret_cast<const PacketType*>((const char*)data)[0];
	qDebug() << "Packet" << type.packetType;
	qDebug() << "\tsecondary?" << type.secondary;
	qDebug() << "\tparam" << type.param;

	if(type.packetType == 0){
		inst->scheduler->NoteOn(scale.GetNote((int)data[2], (int)data[3]));
	}
	
	// for (int i = 0; i < data.size(); i++){
	// 	qDebug() << (int)data[i];
	// }
}