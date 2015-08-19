#include "moc_clientgui.h"
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
// #include <QtGui/QVerticalLayout>
#include <QtGui/QGridLayout>

ClientGUI::ClientGUI(QWidget* p): QTabWidget(p){
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	auto grid = new QHBoxLayout(nullptr);
	auto tab = new QWidget();
	auto l = new QLabel("Client lol");

	grid->addStretch(1);
	grid->addWidget(l);
	grid->addStretch(1);

	tab->setLayout(grid);
	tab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	addTab(tab, "Blah");
	addTab(new QWidget(), "Blah");
	addTab(new QWidget(), "Blah");
}