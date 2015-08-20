#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QtGui/QTabWidget>
#include "common.h"

class DiscreteDial;
class AnalogDial;

class ClientGUI : public QTabWidget {
	Q_OBJECT
public:
	DiscreteDial* oscWaveforms[2];
	AnalogDial* oscDetune[2];
	AnalogDial* oscPulseWidth[2];

	DiscreteDial* envType[2];
	AnalogDial* envAttack[2];
	AnalogDial* envDecay[2];
	AnalogDial* envSustain[2];
	AnalogDial* envRelease[2];

public:
	ClientGUI(QWidget* = nullptr);

public slots:
	void osc1WaveformChange(int);
	void osc2WaveformChange(int);
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
};

#endif