#include "moc_serverlogic.h"
#include "instrumentmanager.h"
#include "instrument.h"
#include "notescheduler.h"
#include "packet.h"

#include <cassert>

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

	connect(serverNetwork, SIGNAL(ClientConnect(u32)), this, SLOT(ClientConnected(u32)));
	connect(serverNetwork, SIGNAL(ClientDisconnect(u32)), this, SLOT(ClientDisconnected(u32)));
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
void ServerLogic::ClientDisconnected(u32 id) {
	instrumentManager->DestroyInstrument(id);
}

void ServerLogic::HandleData(QByteArray data, u32 id) {
	auto inst = instrumentManager->GetInstrument(id);

	auto type = *reinterpret_cast<const PacketType*>((const char*)data);
	qDebug() << "Packet" << type.packetType;

	if(type.packetType == 0){ // Note on/off
		assert(data.size() >= (s32)sizeof(PacketNote));
		auto packet = reinterpret_cast<const PacketNote*>((const char*)data);
		auto note = scale.GetNote(packet->degree, packet->octave);
		qDebug() << note;

		if(packet->state){
			inst->scheduler->NoteOn(note);
		}else{
			inst->scheduler->NoteOff(note);
		}
		
	}else if(type.packetType == 1){ // Set scale
		assert(data.size() >= (s32)sizeof(PacketScale));
		auto packet = reinterpret_cast<const PacketScale*>((const char*)data);
		scale.ConstructScale(packet->rootNote, packet->scaleType);
		instrumentManager->ForEachInstrument([](Instrument& i){
			i.scheduler->SoftClear();
		});

	}else if(type.packetType == 2){ // Mode change
		assert(data.size() >= (s32)sizeof(PacketModeConfig));
		auto packet = reinterpret_cast<const PacketModeConfig*>((const char*)data);
		qDebug() << "\tsecondary?" << type.secondary;
		qDebug() << "Mode change" << type.param << "to" << packet->value;

		inst->SetParameter((Parameters)type.param, packet->value, type.secondary);

	}else if(type.packetType == 3){ // Param change
		assert(data.size() >= (s32)sizeof(PacketParamConfig));
		auto packet = reinterpret_cast<const PacketParamConfig*>((const char*)data);
		qDebug() << "\tsecondary?" << type.secondary;
		qDebug() << "Param change" << type.param << "to" << packet->value;

		if((Parameters)type.param == Parameters::Tempo){
			tempo = packet->value;
		}else{
			inst->SetParameter((Parameters)type.param, packet->value, type.secondary);
		}
	}
}