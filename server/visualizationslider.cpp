#include "visualizationslider.h"

#include <QtGui/QPainter>
#include <QtGui/QStyleOptionSlider>

VisualizationSlider::VisualizationSlider(QWidget* p) : QSlider(p), color("#fff") {}

void VisualizationSlider::DrawText(QPainter* p, const QRect& r) {
	auto color = QColor("#222");

	auto font = p->font();
	p->setPen(color);

	font.setWeight(QFont::Bold);
	p->setFont(font);
	if (r.width() > 2)
	{
		p->drawText(r, Qt::AlignCenter, text);
	}
}

void VisualizationSlider::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setPen(Qt::NoPen);

	QStyleOptionSlider style;
	style.init(this);

	auto r = style.rect;

	auto sectHeight = height();// * 100 / 100; Using this for scaling eventually

	p.setBrush(QColor("#333"));
	r.setY(height() - sectHeight);
	r.setHeight(sectHeight);
	p.drawRect(r);

	p.setBrush(color);
	auto nh = 15 + ((sectHeight - 15) * value() / 100);
	r.setY(height() - sectHeight / 2 - nh / 2);
	r.setHeight(nh);

	p.drawRect(r);

	r = QRect(0, height() - sectHeight / 2 - 75, width(), 150);

	DrawText(&p, r);
}