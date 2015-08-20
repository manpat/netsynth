#include "moc_clientgui.h"
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
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
		osc1->addWidget(new QLabel("Oscillator 1"));
		osc2->addWidget(new QLabel("Oscillator 2"));

		{
			osc1->addWidget(new CustomDial());
			osc1->addWidget(new CustomDial());
			osc1->addWidget(new CustomDial());
			osc1->addWidget(new CustomDial());
		}
		{
			osc2->addWidget(new CustomDial());
			osc2->addWidget(new CustomDial());
			osc2->addWidget(new CustomDial());
			osc2->addWidget(new CustomDial());
		}

		set->addLayout(osc1);
		set->addLayout(osc2);
		oscillatorTab->setLayout(set);
	}

	addTab(oscillatorTab, "Oscillators");
	addTab(envelopeTab, "Envelopes");
	addTab(serverTab, "Server");
}