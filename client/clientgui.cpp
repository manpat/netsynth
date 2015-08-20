#include "moc_clientgui.h"
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGroupBox>
// #include <QtGui/QVBoxLayout>
// #include <QtGui/QGridLayout>

#include "argslot.h"
#include "customdial.h"
#include "typedefinitions.h"

ClientGUI::ClientGUI(QWidget* p): QTabWidget(p){
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setTabPosition(South);

	auto oscillatorTab = new QWidget();
	auto envelopeTab = new QWidget();
	auto serverTab = new QWidget();

	oscillatorTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	envelopeTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	serverTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	{
		auto set = new QVBoxLayout();

		for(int i = 0; i < 2; i++){
			auto box = new QHBoxLayout();

			oscWaveforms[i] = new DiscreteDial();
			oscWaveforms[i]->setColor("#dd3");
			oscWaveforms[i]->setSteps((int)OscillatorWaveform::Count);

			oscDetune[i] = new AnalogDial();
			oscPulseWidth[i] = new AnalogDial();

			box->addWidget(oscWaveforms[i]);
			box->addWidget(oscDetune[i]);
			box->addWidget(oscPulseWidth[i]);

			connect(oscWaveforms[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1WaveformChange(int), i+1)));
			connect(oscDetune[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1DetuneChange(int), i+1)));
			connect(oscPulseWidth[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1PulseWidthChange(int), i+1)));

			oscWaveforms[i]->setValue(1);
			oscWaveforms[i]->setValue(0);
			oscDetune[i]->setValue(1);
			oscDetune[i]->setValue(0);
			oscPulseWidth[i]->setValue(50);

			auto oscbox = new QGroupBox(QString("Oscillator %1").arg(i+1));
			oscbox->setLayout(box);
			set->addWidget(oscbox);
		};

		set->setContentsMargins(20, 20, 20, 20);
		oscillatorTab->setLayout(set);
	}

	{
		auto set = new QVBoxLayout();
		for(int i = 0; i < 2; i++){
			auto box = new QHBoxLayout();

			envType[i] = new DiscreteDial();
			envType[i]->setColor("#dd3");
			envType[i]->setSteps((int)EnvelopeType::Count);

			envAttack [i] = new AnalogDial();
			envDecay  [i] = new AnalogDial();
			envSustain[i] = new AnalogDial();
			envRelease[i] = new AnalogDial();

			box->addWidget(envType[i]);
			box->addWidget(envAttack[i]);
			box->addWidget(envDecay[i]);
			box->addWidget(envSustain[i]);
			box->addWidget(envRelease[i]);

			auto oscbox = new QGroupBox(QString("Envelope %1").arg(i+1));
			oscbox->setLayout(box);
			set->addWidget(oscbox);

			connect(envType[i], SIGNAL(valueChanged(int)), this, ARGSLOT(env%1TypeChange(int), i+1)));
			connect(envAttack[i], SIGNAL(valueChanged(int)), this, ARGSLOT(env%1AttackChange(int), i+1)));
			connect(envDecay[i], SIGNAL(valueChanged(int)), this, ARGSLOT(env%1DecayChange(int), i+1)));
			connect(envSustain[i], SIGNAL(valueChanged(int)), this, ARGSLOT(env%1SustainChange(int), i+1)));
			connect(envRelease[i], SIGNAL(valueChanged(int)), this, ARGSLOT(env%1ReleaseChange(int), i+1)));
		}

		set->setContentsMargins(20, 20, 20, 20);
		envelopeTab->setLayout(set);
	}

	{
		auto box = new QHBoxLayout();

		servScale = new DiscreteDial();
		servScale->setColor("#dd3");
		servScale->setSteps((int)Notes::Count);

		servTempo = new AnalogDial();

		box->addWidget(servScale);
		box->addWidget(servTempo);

		connect(servScale, SIGNAL(valueChanged(int)), this, SLOT(servScaleChange(int)));
		connect(servTempo, SIGNAL(valueChanged(int)), this, SLOT(servTempoChange(int)));

		box->setContentsMargins(20, 20, 20, 20);
		serverTab->setLayout(box);
	}

	addTab(oscillatorTab, "Oscillators");
	addTab(envelopeTab, "Envelopes");
	addTab(serverTab, "Server");
}

void ClientGUI::osc1WaveformChange(int v){
	switch(v){
		case 0: oscWaveforms[0]->setText("None"); break;
		case 1: oscWaveforms[0]->setText("Sine"); break;
		case 2: oscWaveforms[0]->setText("Square"); break;
		case 3: oscWaveforms[0]->setText("Triangle"); break;
		case 4: oscWaveforms[0]->setText("Saw"); break;
		default: oscWaveforms[0]->setText("unknown"); break;
	}
}
void ClientGUI::osc2WaveformChange(int v){
	switch(v){
		case 0: oscWaveforms[1]->setText("None"); break;
		case 1: oscWaveforms[1]->setText("Sine"); break;
		case 2: oscWaveforms[1]->setText("Square"); break;
		case 3: oscWaveforms[1]->setText("Triangle"); break;
		case 4: oscWaveforms[1]->setText("Saw"); break;
		default: oscWaveforms[1]->setText("unknown"); break;
	}
}
void ClientGUI::osc1DetuneChange(int v){
	oscDetune[0]->setText(QString::number(v));
}
void ClientGUI::osc2DetuneChange(int v){
	oscDetune[1]->setText(QString::number(v));
}
void ClientGUI::osc1PulseWidthChange(int v){
	oscPulseWidth[0]->setText(QString("%1%").arg(v));
}
void ClientGUI::osc2PulseWidthChange(int v){
	oscPulseWidth[1]->setText(QString("%1%").arg(v));
}


void ClientGUI::env1TypeChange(int v){
	switch((EnvelopeType)v){
		case EnvelopeType::None:	envType[0]->setText("None"); break;
		case EnvelopeType::DC:		envType[0]->setText("DC"); break;
		case EnvelopeType::Linear:	envType[0]->setText("Linear"); break;
		case EnvelopeType::AR:		envType[0]->setText("AR"); break;
		case EnvelopeType::ADSR:	envType[0]->setText("ADSR"); break;
		default: envType[0]->setText("unknown"); break;
	}
}
void ClientGUI::env1AttackChange(int v){
	envAttack[0]->setText(QString("%1ms").arg(v));
}
void ClientGUI::env1DecayChange(int v){
	envDecay[0]->setText(QString("%1ms").arg(v));
}
void ClientGUI::env1SustainChange(int v){
	envSustain[0]->setText(QString("%1%").arg(v));
}
void ClientGUI::env1ReleaseChange(int v){
	envRelease[0]->setText(QString("%1ms").arg(v));
}

void ClientGUI::env2TypeChange(int v){
	switch((EnvelopeType)v){
		case EnvelopeType::None:	envType[1]->setText("None"); break;
		case EnvelopeType::DC:		envType[1]->setText("DC"); break;
		case EnvelopeType::Linear:	envType[1]->setText("Linear"); break;
		case EnvelopeType::AR:		envType[1]->setText("AR"); break;
		case EnvelopeType::ADSR:	envType[1]->setText("ADSR"); break;
		default: envType[1]->setText("unknown"); break;
	}
}
void ClientGUI::env2AttackChange(int v){
	envAttack[1]->setText(QString("%1ms").arg(v));
}
void ClientGUI::env2DecayChange(int v){
	envDecay[1]->setText(QString("%1ms").arg(v));
}
void ClientGUI::env2SustainChange(int v){
	envSustain[1]->setText(QString("%1%").arg(v));
}
void ClientGUI::env2ReleaseChange(int v){
	envRelease[1]->setText(QString("%1ms").arg(v));
}

void ClientGUI::servScaleChange(int v){
	switch(v){
		case 0:  servScale->setText("None"); break;
		case 1:  servScale->setText("DC"); break;
		case 2:  servScale->setText("Linear"); break;
		case 3:  servScale->setText("AR"); break;
		case 4:  servScale->setText("ADSR"); break;
		default: servScale->setText("unknown"); break;
	}
}
void ClientGUI::servTempoChange(int v){
	servTempo->setText(QString("%1bps").arg(v));
}
