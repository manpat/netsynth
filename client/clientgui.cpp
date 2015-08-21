#include "moc_clientgui.h"
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGroupBox>
// #include <QtGui/QVBoxLayout>
// #include <QtGui/QGridLayout>
#include <QtGui/QKeyEvent>
#include <QtCore/QDebug>

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

			oscOctave[i] = new DiscreteDial();
			oscOctave[i]->setRange(-2, 2);

			oscDetune[i] = new AnalogDial();
			oscPulseWidth[i] = new AnalogDial();

			box->addWidget(oscWaveforms[i]);
			box->addWidget(oscOctave[i]);
			box->addWidget(oscDetune[i]);
			box->addWidget(oscPulseWidth[i]);

			connect(oscWaveforms[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1WaveformChange(int), i+1)));
			connect(oscOctave[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1OctaveChange(int), i+1)));
			connect(oscDetune[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1DetuneChange(int), i+1)));
			connect(oscPulseWidth[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1PulseWidthChange(int), i+1)));

			oscDetune[i]->setRange(-100, 100);

			oscWaveforms[i]->setValue(1);
			oscWaveforms[i]->setValue(0);
			oscOctave[i]->setValue(1);
			oscOctave[i]->setValue(0);
			oscDetune[i]->setValue(1);
			oscDetune[i]->setValue(0);
			oscPulseWidth[i]->setValue(50);

			auto oscbox = new QGroupBox(QString("Oscillator %1").arg(i+1));
			oscbox->setLayout(box);
			set->addWidget(oscbox);
		};

		oscWaveforms[0]->setValue(1);

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

			envAttack [i]->setRange(5, 2000);
			envDecay  [i]->setRange(5, 2000);
			envRelease[i]->setRange(5, 6000);

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

			envType[i]->setValue((int)EnvelopeType::ADSR);
			envAttack[i]->setValue(10);
			envDecay[i]->setValue(50);
			envSustain[i]->setValue(70);
			envRelease[i]->setValue(100);
		}

		set->setContentsMargins(20, 20, 20, 20);
		envelopeTab->setLayout(set);
	}

	{
		auto box = new QHBoxLayout();

		servScale = new DiscreteDial();
		servScale->setColor("#dd3");
		servScale->setRange((int)Notes::A, (int)Notes::Gs);

		servTempo = new AnalogDial();
		servTempo->setRange(40, 240);

		box->addWidget(servScale);
		box->addWidget(servTempo);

		connect(servScale, SIGNAL(valueChanged(int)), this, SLOT(servScaleChange(int)));
		connect(servTempo, SIGNAL(valueChanged(int)), this, SLOT(servTempoChange(int)));

		servScale->setValue((int)Notes::B);
		servScale->setValue((int)Notes::A);
		servTempo->setValue(60);

		box->setContentsMargins(20, 20, 20, 20);
		serverTab->setLayout(box);
	}

	addTab(oscillatorTab, "Oscillators");
	addTab(envelopeTab, "Envelopes");
	addTab(serverTab, "Server");

	installEventFilter(this);
}

bool ClientGUI::eventFilter(QObject*, QEvent* event) {
	if(event->type() == QEvent::KeyPress){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		auto note = keyboardMap.FindNote(keyevent->nativeScanCode());
		if (note.first != -100) {
			emit notifyNoteChange(note.first, note.second, 1);
		}

	}else if(event->type() == QEvent::KeyRelease){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		auto note = keyboardMap.FindNote(keyevent->nativeScanCode());
		if (note.first != -100) {
			emit notifyNoteChange(note.first, note.second, 0);
		}

	}else{
		return false;
	}

	return true;
}

void ClientGUI::osc1WaveformChange(int v){
	switch((OscillatorWaveform)v){
		case OscillatorWaveform::None: oscWaveforms[0]->setText("None"); break;
		case OscillatorWaveform::Sine: oscWaveforms[0]->setText("Sine"); break;
		case OscillatorWaveform::Square: oscWaveforms[0]->setText("Square"); break;
		case OscillatorWaveform::Triangle: oscWaveforms[0]->setText("Triangle"); break;
		case OscillatorWaveform::Saw: oscWaveforms[0]->setText("Saw"); break;
		default: oscWaveforms[0]->setText("unknown"); return;
	}

	emit notifyModeChange(Parameters::Waveform, false, v);
}
void ClientGUI::osc2WaveformChange(int v){
	switch((OscillatorWaveform)v){
		case OscillatorWaveform::None: oscWaveforms[1]->setText("None"); break;
		case OscillatorWaveform::Sine: oscWaveforms[1]->setText("Sine"); break;
		case OscillatorWaveform::Square: oscWaveforms[1]->setText("Square"); break;
		case OscillatorWaveform::Triangle: oscWaveforms[1]->setText("Triangle"); break;
		case OscillatorWaveform::Saw: oscWaveforms[1]->setText("Saw"); break;
		default: oscWaveforms[1]->setText("unknown"); return;
	}

	emit notifyModeChange(Parameters::Waveform, true, v);
}
void ClientGUI::osc1OctaveChange(int v){
	if(v >= 0){
		oscOctave[0]->setText(QString("+%1").arg(v));
	}else{
		oscOctave[0]->setText(QString("%1").arg(v));
	}
	emit notifyParamChange(Parameters::OctaveShift, false, std::pow(2.0, (f32)v));
}
void ClientGUI::osc2OctaveChange(int v){
	if(v >= 0){
		oscOctave[1]->setText(QString("+%1").arg(v));
	}else{
		oscOctave[1]->setText(QString("%1").arg(v));
	}
	emit notifyParamChange(Parameters::OctaveShift, true, std::pow(2.0, (f32)v));
}
void ClientGUI::osc1DetuneChange(int v){
	oscDetune[0]->setText(QString("%1%").arg(v));
	emit notifyParamChange(Parameters::Detune, false, std::pow(2.0, v/100.0));
}
void ClientGUI::osc2DetuneChange(int v){
	oscDetune[1]->setText(QString("%1%").arg(v));
	emit notifyParamChange(Parameters::Detune, true, std::pow(2.0, v/100.0));
}
void ClientGUI::osc1PulseWidthChange(int v){
	oscPulseWidth[0]->setText(QString("%1%").arg(v));
	emit notifyParamChange(Parameters::PulseWidth, false, v/100.f);
}
void ClientGUI::osc2PulseWidthChange(int v){
	oscPulseWidth[1]->setText(QString("%1%").arg(v));
	emit notifyParamChange(Parameters::PulseWidth, true, v/100.f);
}


void ClientGUI::env1TypeChange(int v){
	switch((EnvelopeType)v){
		case EnvelopeType::None:	envType[0]->setText("None"); break;
		case EnvelopeType::DC:		envType[0]->setText("DC"); break;
		case EnvelopeType::Linear:	envType[0]->setText("Linear"); break;
		case EnvelopeType::AR:		envType[0]->setText("AR"); break;
		case EnvelopeType::ADSR:	envType[0]->setText("ADSR"); break;
		default: envType[0]->setText("unknown"); return;
	}

	emit notifyModeChange(Parameters::EnvelopeType, false, v);
}
void ClientGUI::env1AttackChange(int v){
	envAttack[0]->setText(QString("%1ms").arg(v));
	emit notifyParamChange(Parameters::Attack, false, v/1000.f);
}
void ClientGUI::env1DecayChange(int v){
	envDecay[0]->setText(QString("%1ms").arg(v));
	emit notifyParamChange(Parameters::Decay, false, v/1000.f);
}
void ClientGUI::env1SustainChange(int v){
	envSustain[0]->setText(QString("%1%").arg(v));
	emit notifyParamChange(Parameters::Sustain, false, v/100.f);
}
void ClientGUI::env1ReleaseChange(int v){
	envRelease[0]->setText(QString("%1ms").arg(v));
	emit notifyParamChange(Parameters::Release, false, v/1000.f);
}

void ClientGUI::env2TypeChange(int v){
	switch((EnvelopeType)v){
		case EnvelopeType::None:	envType[1]->setText("None"); break;
		case EnvelopeType::DC:		envType[1]->setText("DC"); break;
		case EnvelopeType::Linear:	envType[1]->setText("Linear"); break;
		case EnvelopeType::AR:		envType[1]->setText("AR"); break;
		case EnvelopeType::ADSR:	envType[1]->setText("ADSR"); break;
		default: envType[1]->setText("unknown"); return;
	}

	emit notifyModeChange(Parameters::EnvelopeType, true, v);
}
void ClientGUI::env2AttackChange(int v){
	envAttack[1]->setText(QString("%1ms").arg(v));
	emit notifyParamChange(Parameters::Attack, true, v/1000.f);
}
void ClientGUI::env2DecayChange(int v){
	envDecay[1]->setText(QString("%1ms").arg(v));
	emit notifyParamChange(Parameters::Decay, true, v/1000.f);
}
void ClientGUI::env2SustainChange(int v){
	envSustain[1]->setText(QString("%1%").arg(v));
	emit notifyParamChange(Parameters::Sustain, true, v/100.f);
}
void ClientGUI::env2ReleaseChange(int v){
	envRelease[1]->setText(QString("%1ms").arg(v));
	emit notifyParamChange(Parameters::Release, true, v/1000.f);
}

void ClientGUI::servScaleChange(int v){
	switch((Notes)v){
		case Notes::A :  servScale->setText("A"); break;
		case Notes::As:  servScale->setText("A#"); break;
		case Notes::B :  servScale->setText("B"); break;
		case Notes::C :  servScale->setText("C"); break;
		case Notes::Cs:  servScale->setText("C#"); break;
		case Notes::D :  servScale->setText("D"); break;
		case Notes::Ds:  servScale->setText("D#"); break;
		case Notes::E :  servScale->setText("E"); break;
		case Notes::F :  servScale->setText("F"); break;
		case Notes::Fs:  servScale->setText("F#"); break;
		case Notes::G :  servScale->setText("G"); break;
		case Notes::Gs:  servScale->setText("G#"); break;
		default: servScale->setText("unknown"); return;
	}

	emit notifyScaleChange(ScaleType::Pentatonic, (Notes)v);
}
void ClientGUI::servTempoChange(int v){
	servTempo->setText(QString("%1bps").arg(v));
	emit notifyParamChange(Parameters::Tempo, false, v);
}
