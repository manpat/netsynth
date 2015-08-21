#ifndef VISUALIZATIONSLIDER_H
#define VISUALIZATIONSLIDER_H

#include <QSlider>
#include <QPainter>
#include <QStyleOptionSlider>

class VisualizationSlider : public QSlider {
public:
	VisualizationSlider(QWidget* p = nullptr) : QSlider(p), color("#fff") {}

	void setColor(const QColor& c) { color = c; }
	void setText(const QString& t) { text = t; }

protected:
	QColor color;
	QString text;

	void paintEvent(QPaintEvent*) override {
		QPainter p(this);
		p.setPen(Qt::NoPen);

		QStyleOptionSlider style;
		style.init(this);

		bool hover = style.state & QStyle::State_MouseOver;
		auto& r = style.rect;

		if (hover) p.setBrush(QColor("#393939"));
		else p.setBrush(QColor("#333"));

		p.drawRect(r);

		if (hover) p.setBrush(color.lighter(120));
		else p.setBrush(color);

		if (orientation() == Qt::Vertical) {
			auto nh = height()*value() / 100;
			r.setY(height() - nh);
			r.setHeight(nh);
		}
		else {
			auto nh = width()*value() / 100;
			r.setWidth(nh);
		}

		p.drawRect(r);
	}
	
};

#endif//VISUALIZATIONSLIDER_H