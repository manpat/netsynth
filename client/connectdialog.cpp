#include "moc_connectdialog.h"

#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QRegExpValidator>

#include <QtCore/QDebug>
#include <QtCore/QRegExp>

ConnectDialog::ConnectDialog(QWidget* p)
	: QDialog(p){

	auto label = new QLabel("Enter server IP");
	auto gobutton = new QPushButton;

	input = new QLineEdit;
	input->setValidator(new QRegExpValidator(QRegExp(R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})")));

	label->setBuddy(input);
	connect(gobutton, SIGNAL(pressed()), this, SLOT(doConnect()));

	auto hbox = new QHBoxLayout;
	hbox->addWidget(label);
	hbox->addWidget(input);
	hbox->addWidget(gobutton);
	setLayout(hbox);
	setWindowTitle("Connect to server");
}

void ConnectDialog::doConnect(){
	if(!input->hasAcceptableInput()) return;

	qDebug() << "DO CONNECT PLOX " << input->text();
	emit requestConnect(input->text());
}