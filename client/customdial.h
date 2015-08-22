#ifndef CUSTOMDIAL_H
#define CUSTOMDIAL_H

#include <QtGui/QDial>

class QPainter;
class QRect;

class BaseDial : public QDial {
public:
	BaseDial(QWidget* parent = nullptr);

	void setColor(const QColor&);
	void setText(const QString&);
	void setName(const QString&);
	void setEnabled(bool);

protected:
	QColor color;
	QString text;
	QString name;
	bool enabled;

	void DrawText(QPainter*, const QRect&);
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