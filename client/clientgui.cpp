#include "moc_clientgui.h"
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGroupBox>
// #include <QtGui/QVBoxLayout>
// #include <QtGui/QGridLayout>

#include "customdial.h"

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
		auto set  = new QVBoxLayout();
		auto osc1 = new QHBoxLayout();
		auto osc2 = new QHBoxLayout();

		{
			osc1->addWidget(new DiscreteDial());
			osc1->addWidget(new AnalogDial());
			osc1->addWidget(new AnalogDial());
			osc1->addWidget(new AnalogDial());
		}
		{
			osc2->addWidget(new DiscreteDial());
			osc2->addWidget(new AnalogDial());
			osc2->addWidget(new AnalogDial());
			// osc2->addWidget(new AnalogDial());
			// osc2->addWidget(new AnalogDial());
		}

		auto osc1box = new QGroupBox("Oscillator 1");
		auto osc2box = new QGroupBox("Oscillator 2");
		osc1box->setLayout(osc1);
		osc2box->setLayout(osc2);

		set->addWidget(osc1box);
		set->addWidget(osc2box);
		set->setContentsMargins(20, 20, 20, 20);
		oscillatorTab->setLayout(set);
	}

	addTab(oscillatorTab, "Oscillators");
	addTab(envelopeTab, "Envelopes");
	addTab(serverTab, "Server");
}