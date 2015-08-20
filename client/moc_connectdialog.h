#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QtGui/QDialog>

class QLineEdit;

class ConnectDialog : public QDialog {
	Q_OBJECT
protected:
	QLineEdit* input;

public:
	ConnectDialog(QWidget* = nullptr);

private slots:
	void doConnect();

signals:
	void requestConnect(const QString&);
};

#endif