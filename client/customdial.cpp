#include "customdial.h"
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionSlider>

CustomDial::CustomDial(QWidget* p) : QDial(p), color("#3d3"){}

void CustomDial::setColor(const QColor& c){
	color = c;
}

void CustomDial::paintEvent(QPaintEvent*){
	QPainter p(this);

	QStyleOptionSlider style;
	style.init(this);

	bool hover = style.state & QStyle::State_MouseOver;

	p.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
	QBrush brush("#333");
	if(hover) brush.setColor("#393939");

	auto diff = width() - height();
	auto diffx = std::max(0, diff) / 2;
	auto diffy = std::max(0,-diff) / 2;

	auto r = style.rect;
	r.adjust(diffx, diffy,-diffx,-diffy); // Squarify

	p.setPen(Qt::NoPen);
	p.setBrush(brush);
	p.drawPie(r.adjusted(20, 20,-20,-20), (220)*16, -(360-100)*16);

	if(hover) p.setPen(QPen(color.lighter(120), 15));
	else p.setPen(QPen(color, 15));
	p.drawArc(r.adjusted(10, 10,-10,-10), 220*16, -(360-100)*16*value()/100);
}
