#ifndef VISUALIZATIONSLIDER_H
#define VISUALIZATIONSLIDER_H

#include <QtGui/QSlider>
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionSlider>

class VisualizationSlider : public QSlider {
public:
	VisualizationSlider(QWidget* parent = nullptr);

	void setColor(const QColor& c) { color = c; }
	void setText(const QString& t) { text = t; }

protected:
	QColor color;
	QString text;

	void DrawText(QPainter*, const QRect&);
	void paintEvent(QPaintEvent*) override;
};

#endif//VISUALIZATIONSLIDER_H