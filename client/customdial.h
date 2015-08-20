#ifndef CUSTOMDIAL_H
#define CUSTOMDIAL_H

#include <QtGui/QDial>

class AnalogDial : public QDial {
public:
	AnalogDial(QWidget* parent = nullptr);

	void setColor(const QColor&);

protected:
	void paintEvent(QPaintEvent*) override;

	QColor color;
};

class DiscreteDial : public QDial {
public:
	DiscreteDial(QWidget* parent = nullptr);

	void setColor(const QColor&);
	void setSteps(int);

protected:
	void paintEvent(QPaintEvent*) override;

	QColor color;
};

#endif