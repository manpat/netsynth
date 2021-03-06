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
	auto miscTab = new QWidget();

	oscillatorTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	envelopeTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	miscTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	{
		auto set = new QVBoxLayout();

		for(int i = 0; i < 2; i++){
			auto box = new QHBoxLayout();

			oscWaveforms[i] = new DiscreteDial();
			oscWaveforms[i]->setColor("#dd3");
			oscWaveforms[i]->setSteps((int)OscillatorWaveform::Count);
			oscWaveforms[i]->setName("Waveform");

			oscOctave[i] = new DiscreteDial();
			oscOctave[i]->setRange(-1, 1);
			oscOctave[i]->setName("Octave");

			oscDetune[i] = new AnalogDial();
			oscDetune[i]->setPageStep(1);
			oscDetune[i]->setName("Detune");

			oscPulseWidth[i] = new AnalogDial();
			oscPulseWidth[i]->setPageStep(1);
			oscPulseWidth[i]->setName("PulseWidth");

			box->addWidget(oscWaveforms[i]);
			box->addWidget(oscOctave[i]);
			// box->addWidget(oscDetune[i]);
			box->addWidget(oscPulseWidth[i]);

			connect(oscWaveforms[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1WaveformChange(int), i+1)), Qt::QueuedConnection);
			connect(oscOctave[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1OctaveChange(int), i+1)), Qt::QueuedConnection);
			connect(oscDetune[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1DetuneChange(int), i+1)), Qt::QueuedConnection);
			connect(oscPulseWidth[i], SIGNAL(valueChanged(int)), this, ARGSLOT(osc%1PulseWidthChange(int), i+1)), Qt::QueuedConnection);

			oscDetune[i]->setRange(-100, 100);

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

			envAttack [i]->setRange(5, 2000);
			envDecay  [i]->setRange(5, 2000);
			envRelease[i]->setRange(5, 6000);

			envType   [i]->setName("EnvelopeType");
			envAttack [i]->setName("Attack");
			envDecay  [i]->setName("Decay");
			envSustain[i]->setName("Sustain");
			envRelease[i]->setName("Release");

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
		auto set = new QHBoxLayout();
		{
			auto box = new QVBoxLayout();
			auto volRevBox = new QHBoxLayout();
			instQuantise = new DiscreteDial();
			instQuantise->setColor("#dd3");
			instQuantise->setName("Quantisation");
			instQuantise->setSteps((int)QuantisationSetting::Count);

			instVolume = new AnalogDial();
			instVolume->setName("Volume");

			instReverb = new AnalogDial();
			instReverb->setName("Reverb");
			instReverb->setRange(0, 20000);

			volRevBox->addWidget(instVolume);
			volRevBox->addWidget(instReverb);

			box->addWidget(instQuantise);
			box->addLayout(volRevBox);

			auto oscbox = new QGroupBox("Instrument");
			oscbox->setStyleSheet("QGroupBox::title { subcontrol-position: hcenter; }");
			oscbox->setLayout(box);
			set->addWidget(oscbox);

			connect(instQuantise, SIGNAL(valueChanged(int)), this, SLOT(instQuantiseChange(int)));
			connect(instVolume, SIGNAL(valueChanged(int)), this, SLOT(instVolumeChange(int)));
			connect(instReverb, SIGNAL(valueChanged(int)), this, SLOT(instReverbChange(int)));
		}

		{
			auto box = new QVBoxLayout();
			auto scaleBox = new QHBoxLayout();
			servScale = new DiscreteDial();
			servScale->setColor("#dd3");
			servScale->setName("Key");
			servScale->setRange((int)Notes::A, (int)Notes::Gs);
			
			servScaleType = new DiscreteDial();
			servScaleType->setColor("#dd3");
			servScaleType->setName("Type");
			servScaleType->setRange((int)ScaleType::Major, (int)ScaleType::Count-1);

			servTempo = new AnalogDial();
			servTempo->setRange(40, 240);
			servTempo->setName("Tempo");

			scaleBox->addWidget(servScale);
			scaleBox->addWidget(servScaleType);
			box->addLayout(scaleBox);
			box->addWidget(servTempo);

			auto oscbox = new QGroupBox("Server");
			oscbox->setStyleSheet("QGroupBox::title { subcontrol-position: hcenter; }");
			oscbox->setLayout(box);
			set->addWidget(oscbox);

			connect(servScale, SIGNAL(valueChanged(int)), this, SLOT(servScaleChange(int)));
			connect(servTempo, SIGNAL(valueChanged(int)), this, SLOT(servTempoChange(int)));
			connect(servScaleType, SIGNAL(valueChanged(int)), this, SLOT(servScaleTypeChange(int)));

			servScale->setValue((int)Notes::B);
			servScale->setValue((int)Notes::A);
			servScaleType->setValue((int)ScaleType::Minor);
			servScaleType->setValue((int)ScaleType::Major);
			servTempo->setValue(60);
		}

		set->setContentsMargins(20, 20, 20, 20);
		miscTab->setLayout(set);
	}

	addTab(oscillatorTab, "Oscillators");
	addTab(envelopeTab, "Envelopes");
	addTab(miscTab, "Miscellaneous");

	installEventFilter(this);
}

/*
	                                             
	 ad88888ba  88                               
	d8"     "8b 88              ,d               
	Y8,         88              88               
	`Y8aaaaa,   88  ,adPPYba, MM88MMM ,adPPYba,  
	  `"""""8b, 88 a8"     "8a  88    I8[    ""  
	        `8b 88 8b       d8  88     `"Y8ba,   
	Y8a     a8P 88 "8a,   ,a8"  88,   aa    ]8I  
	 "Y88888P"  88  `"YbbdP"'   "Y888 `"YbbdP"'  
	                                             
	                                             
*/
bool ClientGUI::eventFilter(QObject*, QEvent* event) {
	if(event->type() == QEvent::KeyPress){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		auto note = keyboardMap.FindNote(keyevent->key());
		if (note.first != -100) {
			emit notifyNoteChange(note.first, note.second, 1);
		}

	}else if(event->type() == QEvent::KeyRelease){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		auto note = keyboardMap.FindNote(keyevent->key());
		if (note.first != -100) {
			emit notifyNoteChange(note.first, note.second, 0);
		}

	}else{
		return false;
	}

	return true;
}

void ClientGUI::SetDefaults(){
	for(int i = 0; i < 2; i++){
		oscOctave[i]->setValue(1);
		oscOctave[i]->setValue(0);
		oscDetune[i]->setValue(1);
		oscDetune[i]->setValue(0);
		oscPulseWidth[i]->setValue(50);

		envAttack[i]->setValue(10);
		envDecay[i]->setValue(50);
		envSustain[i]->setValue(70);
		envRelease[i]->setValue(400);
	}

	instVolume->setValue(100);
	instQuantise->setValue(1);
	instQuantise->setValue(0);
	instReverb->setValue(1);
	instReverb->setValue(0);
	
	oscWaveforms[0]->setValue(1);
	oscWaveforms[1]->setValue(1);
	oscWaveforms[1]->setValue(0);
	envType[0]->setValue((int)EnvelopeType::ADSR);
	envType[1]->setValue((int)EnvelopeType::Linear);
	envType[1]->setValue((int)EnvelopeType::None);
}

void ClientGUI::osc1WaveformChange(int v){
	oscPulseWidth[0]->setEnabled((OscillatorWaveform)v == OscillatorWaveform::Square);

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
	oscPulseWidth[1]->setEnabled((OscillatorWaveform)v == OscillatorWaveform::Square);

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
	env[0] = (EnvelopeType)v;
	envDecay[0]->setEnabled(env[0] == EnvelopeType::ADSR);
	envSustain[0]->setEnabled(env[0] == EnvelopeType::ADSR);

	envAttack[0]->setEnabled(env[0] >= EnvelopeType::AR || env[0] == EnvelopeType::DC);
	envRelease[0]->setEnabled(env[0] >= EnvelopeType::Linear);
	
	switch(env[0]){
		case EnvelopeType::None:	envType[0]->setText("None"); break;
		case EnvelopeType::DC:		envType[0]->setText("DC"); break;
		case EnvelopeType::Linear:	envType[0]->setText("Linear"); break;
		case EnvelopeType::AR:		envType[0]->setText("AR"); break;
		case EnvelopeType::ADSR:	envType[0]->setText("ADSR"); break;
		default: envType[0]->setText("unknown"); return;
	}

	emit notifyModeChange(Parameters::EnvelopeType, false, v);

	auto attack = envAttack[0]->value();
	envAttack[0]->setValue(attack+1);
	if(env[0] == EnvelopeType::DC){
		envAttack[0]->setRange(0, 1000);
		envAttack[0]->setName("Value");
	}else{
		envAttack[0]->setRange(5, 2000);
		envAttack[0]->setName("Attack");
	}
	envAttack[0]->setValue(attack); // Force update
}
void ClientGUI::env1AttackChange(int v){
	if(env[0] == EnvelopeType::DC){
		envAttack[0]->setText(QString("%1%").arg(v/10.f));
		emit notifyParamChange(Parameters::Attack, false, v/1000.f);
	}else{
		envAttack[0]->setText(QString("%1ms").arg(v));
		emit notifyParamChange(Parameters::Attack, false, v/1000.f);
	}
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
	env[1] = (EnvelopeType)v;
	envDecay[1]->setEnabled(env[1] == EnvelopeType::ADSR);
	envSustain[1]->setEnabled(env[1] == EnvelopeType::ADSR);

	envAttack[1]->setEnabled(env[1] >= EnvelopeType::AR || env[1] == EnvelopeType::DC);
	envRelease[1]->setEnabled(env[1] >= EnvelopeType::Linear);
	
	switch(env[1]){
		case EnvelopeType::None:	envType[1]->setText("None"); break;
		case EnvelopeType::DC:		envType[1]->setText("DC"); break;
		case EnvelopeType::Linear:	envType[1]->setText("Linear"); break;
		case EnvelopeType::AR:		envType[1]->setText("AR"); break;
		case EnvelopeType::ADSR:	envType[1]->setText("ADSR"); break;
		default: envType[1]->setText("unknown"); return;
	}

	emit notifyModeChange(Parameters::EnvelopeType, true, v);

	auto attack = envAttack[1]->value();
	envAttack[1]->setValue(attack+1);
	if(env[1] == EnvelopeType::DC){
		envAttack[1]->setRange(1, 1000);
		envAttack[1]->setName("Value");
	}else{
		envAttack[1]->setRange(5, 2001);
		envAttack[1]->setName("Attack");
	}
	envAttack[1]->setValue(attack); // Force update
}
void ClientGUI::env2AttackChange(int v){
	if(env[1] == EnvelopeType::DC){
		envAttack[1]->setText(QString("%1%").arg(v/10.f));
		emit notifyParamChange(Parameters::Attack, true, v/1000.f);
	}else{
		envAttack[1]->setText(QString("%1ms").arg(v));
		emit notifyParamChange(Parameters::Attack, true, v/1000.f);
	}
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
	scaleRoot = (Notes)v;

	switch(scaleRoot){
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

	emit notifyScaleChange(scaleType, scaleRoot);
}	
void ClientGUI::servScaleTypeChange(int v){
	scaleType = (ScaleType)v;

	switch(scaleType){
		case ScaleType::Major: servScaleType->setText("Major"); break;
		case ScaleType::Minor: servScaleType->setText("Minor"); break;
		case ScaleType::Pentatonic: servScaleType->setText("Pentatonic"); break;
		default: servScaleType->setText("unknown"); return;
	}

	emit notifyScaleChange(scaleType, scaleRoot);
}
void ClientGUI::servTempoChange(int v){
	servTempo->setText(QString("%1bpm").arg(v));
	emit notifyParamChange(Parameters::Tempo, false, v);
}

void ClientGUI::instQuantiseChange(int v){
	switch((QuantisationSetting)v){
		case QuantisationSetting::None:
			instQuantise->setText("None");
			break;

		case QuantisationSetting::Sixteenth:
			instQuantise->setText("1/16");
			break;

		case QuantisationSetting::Twelfth:
			instQuantise->setText("1/12");
			break;

		case QuantisationSetting::Eighth:
			instQuantise->setText("1/8");
			break;

		case QuantisationSetting::Sixth:
			instQuantise->setText("1/6");
			break;

		case QuantisationSetting::Quarter:
			instQuantise->setText("1/4");
			break;

		case QuantisationSetting::Triplet:
			instQuantise->setText("1/3");
			break;

		case QuantisationSetting::Half:
			instQuantise->setText("1/2");
			break;

		case QuantisationSetting::Whole:
			instQuantise->setText("1/1");
			break;

		default: instQuantise->setText("unknown"); return;
	}

	emit notifyModeChange(Parameters::Quantisation, false, v);
}
void ClientGUI::instVolumeChange(int v){
	instVolume->setText(QString("%1%").arg(v));
	emit notifyParamChange(Parameters::Volume, false, v/100.f);
}
void ClientGUI::instReverbChange(int v){
	instReverb->setText(QString("%1s").arg(v/1000.0));
	emit notifyParamChange(Parameters::Reverb, false, v*1.0f);
}