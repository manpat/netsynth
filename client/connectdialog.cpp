#include "moc_connectdialog.h"

#include <QtGui/QLabel>
#include <QtGui/QToolTip>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QRegExpValidator>

#include <QtCore/QDebug>
#include <QtCore/QRegExp>

#include "moc_clientnetwork.h"

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

	emit requestConnect(input->text());
}

void ConnectDialog::connectResult(int i){
	if(i == 0){
		accept();
	}else{
		QToolTip::showText(input->mapToGlobal(QPoint(0, 0)), "Invalid IP");
	}
}