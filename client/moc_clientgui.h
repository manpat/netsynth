#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QtGui/QTabWidget>
#include "common.h"
#include "typedefinitions.h"
#include "keyboardmap.h"

class DiscreteDial;
class AnalogDial;

class ClientGUI : public QTabWidget {
	Q_OBJECT
protected:
	ScaleType scaleType;
	Notes scaleRoot;
	EnvelopeType env[2];

public:
	KeyboardMap keyboardMap;

	DiscreteDial* oscWaveforms[2];
	DiscreteDial* oscOctave[2];
	AnalogDial* oscDetune[2];
	AnalogDial* oscPulseWidth[2];

	DiscreteDial* envType[2];
	AnalogDial* envAttack[2];
	AnalogDial* envDecay[2];
	AnalogDial* envSustain[2];
	AnalogDial* envRelease[2];

	DiscreteDial* instQuantise;
	AnalogDial* instVolume;

	DiscreteDial* servScale;
	DiscreteDial* servScaleType;
	AnalogDial* servTempo;

public:
	ClientGUI(QWidget* = nullptr);
	bool eventFilter(QObject*, QEvent*) override;

public slots:
	void SetDefaults();

	void osc1WaveformChange(int);
	void osc2WaveformChange(int);
	void osc1OctaveChange(int);
	void osc2OctaveChange(int);
	void osc1DetuneChange(int);
	void osc2DetuneChange(int);
	void osc1PulseWidthChange(int);
	void osc2PulseWidthChange(int);

	void env1TypeChange(int);
	void env1AttackChange(int);
	void env1DecayChange(int);
	void env1SustainChange(int);
	void env1ReleaseChange(int);

	void env2TypeChange(int);
	void env2AttackChange(int);
	void env2DecayChange(int);
	void env2SustainChange(int);
	void env2ReleaseChange(int);

	void servScaleChange(int);
	void servScaleTypeChange(int);
	void servTempoChange(int);

	void instQuantiseChange(int);
	void instVolumeChange(int);

signals:
	void notifyNoteChange(s8 degree, s8 octave, u8 state);
	void notifyModeChange(Parameters paramId, bool secondary, u8 modeValue);
	void notifyParamChange(Parameters paramId, bool secondary, f32 paramValue);
	void notifyScaleChange(ScaleType, Notes);
};

#endif