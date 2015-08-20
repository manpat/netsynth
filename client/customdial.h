#ifndef CUSTOMDIAL_H
#define CUSTOMDIAL_H

#include <QtGui/QDial>

class BaseDial : public QDial {
public:
	BaseDial(QWidget* parent = nullptr);

	void setColor(const QColor&);
	void setText(const QString&);

protected:
	QColor color;
	QString text;
};

class AnalogDial : public BaseDial {
public:
	AnalogDial(QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent*) override;
};

class DiscreteDial : public BaseDial {
public:
	DiscreteDial(QWidget* parent = nullptr);
	void setSteps(int);

protected:
	void paintEvent(QPaintEvent*) override;
};

#endif