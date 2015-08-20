#include "moc_clientgui.h"
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
// #include <QtGui/QVerticalLayout>
#include <QtGui/QGridLayout>

ClientGUI::ClientGUI(QWidget* p): QTabWidget(p){
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setTabPosition(South);

	auto oscillatorTab = new QWidget();
	auto envelopeTab = new QWidget();
	auto serverTab = new QWidget();

	auto grid = new QHBoxLayout(nullptr);
	auto l = new QLabel("Client lol");

	grid->addStretch(1);
	grid->addWidget(l);
	grid->addStretch(1);

	oscillatorTab->setLayout(grid);
	oscillatorTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	addTab(oscillatorTab, "Oscillators");
	addTab(envelopeTab, "Envelopes");
	addTab(serverTab, "Server");
}