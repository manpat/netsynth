#include "moc_serverlogic.h"
#include "moc_servergui.h"
#include "instrumentmanager.h"
#include "instrument.h"
#include "notescheduler.h"
#include "packet.h"

#include <cassert>

Scale ServerLogic::scale;
f32 ServerLogic::tempo = 60.0;

ServerLogic::ServerLogic(){
	serverGUI = new ServerGUI();
	serverGUI->setWindowTitle("Server");
	serverGUI->resize(800, 400);
	serverGUI->show();

	serverNetwork = new ServerNetwork();

	fmodManager.start();
	instrumentManager = new InstrumentManager{&fmodManager, {}};
	scale.ConstructScale(Notes::A, ScaleType::Major);

	connect(&fmodManager, SIGNAL(ready()), this, SLOT(fmodready()));
	connect(serverNetwork, SIGNAL(DataReceived(QByteArray, u32)), this, SLOT(HandleData(QByteArray, u32)));

	connect(serverNetwork, SIGNAL(ClientConnect(u32)), this, SLOT(ClientConnected(u32)));
	connect(serverNetwork, SIGNAL(ClientDisconnect(u32)), this, SLOT(ClientDisconnected(u32)));

	connect(serverNetwork, SIGNAL(ClientConnect(u32)), serverGUI, SLOT(AddSlider(u32)));
	connect(serverNetwork, SIGNAL(ClientDisconnect(u32)), serverGUI, SLOT(RemoveSlider(u32)));

	connect(&fmodManager, SIGNAL(UpdateVisualizer()), this, SLOT(UpdateVisualizer()));
}

ServerLogic::~ServerLogic(){
	fmodManager.kill();
	fmodManager.wait(2000); // Wait max 2s
	fmodManager.terminate(); // Just in case
}

void ServerLogic::fmodready(){
}

void ServerLogic::ClientConnected(u32 id) {
	instrumentManager->NewInstrument(id);
}
void ServerLogic::ClientDisconnected(u32 id) {
	instrumentManager->DestroyInstrument(id);
}

void ServerLogic::HandleData(QByteArray data, u32 id) {
	auto inst = instrumentManager->GetInstrument(id);

	while(data.size() > 0){
		auto type = *reinterpret_cast<const PacketType*>((const char*)data);
		auto param = (Parameters)type.param;

		if(type.packetType == 0){ // Note on/off
			assert(data.size() >= (s32)sizeof(PacketNote));
			auto packet = reinterpret_cast<const PacketNote*>((const char*)data);
			auto note = scale.GetNote(packet->degree, packet->octave);

			if(packet->state){
				inst->scheduler->NoteOn(note);
			}else{
				inst->scheduler->NoteOff(note);
			}

			data.remove(0, sizeof(PacketNote));

		}else if(type.packetType == 1){ // Set scale
			assert(data.size() >= (s32)sizeof(PacketScale));
			auto packet = reinterpret_cast<const PacketScale*>((const char*)data);
			scale.ConstructScale(packet->rootNote, packet->scaleType);
			instrumentManager->ForEachInstrument([](Instrument& i){
				i.scheduler->SoftClear();
			});

			data.remove(0, sizeof(PacketScale));

		}else if(type.packetType == 2){ // Mode change
			assert(data.size() >= (s32)sizeof(PacketModeConfig));
			auto packet = reinterpret_cast<const PacketModeConfig*>((const char*)data);

			inst->SetParameter(param, packet->value, type.secondary);
			data.remove(0, sizeof(PacketModeConfig));

		}else if(type.packetType == 3){ // Param change
			assert(data.size() >= (s32)sizeof(PacketParamConfig));
			auto packet = reinterpret_cast<const PacketParamConfig*>((const char*)data);

			if(param == Parameters::Tempo){
				tempo = packet->value;
			}else{
				inst->SetParameter(param, packet->value, type.secondary);
			}
			data.remove(0, sizeof(PacketParamConfig));
		}
	}
}

void ServerLogic::UpdateVisualizer() {
	for (auto i : instrumentManager->clientInstruments) {
		serverGUI->UpdateSlider(i.first, (int)(std::log(i.second->currentAmplitude+1.0)/2.0*100));
	}
}