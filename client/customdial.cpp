#include "customdial.h"
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionSlider>
#include <QtCore/QDebug>

AnalogDial::AnalogDial(QWidget* p) : QDial(p), color("#3d3"){}

void AnalogDial::setColor(const QColor& c){
	color = c;
}

void AnalogDial::paintEvent(QPaintEvent*){
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
	const auto gap = 90 *16;
	const auto arcsize = 360*16-gap;
	const auto startangle = 270*16 - gap/2;

	p.drawPie(r.adjusted(25, 25,-25,-25), startangle, -arcsize);

	p.setPen(QPen(QColor("#333"), 15));
	p.drawArc(r.adjusted(15, 15,-15,-15), startangle, -arcsize);

	if(hover) p.setPen(QPen(color.lighter(120), 15));
	else p.setPen(QPen(color, 15));
	p.drawArc(r.adjusted(15, 15,-15,-15), startangle, -arcsize*value()/100);
}


DiscreteDial::DiscreteDial(QWidget* p) : QDial(p), color("#dd3"){
	setSteps(5);
}

void DiscreteDial::setColor(const QColor& c){
	color = c;
}

void DiscreteDial::setSteps(int s){
	setMaximum(s-1);
}

void DiscreteDial::paintEvent(QPaintEvent*){
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

	// Note: angles in 1/16ths of a degree
	p.setPen(Qt::NoPen);
	p.setBrush(brush);
	p.drawEllipse(r.adjusted(25, 25,-25,-25));

	const auto gap = 90 *16;
	const auto arcsize = 360*16-gap;
	const auto startangle = 270*16 - gap/2;
	const auto barsize = arcsize/(maximum()+1);

	p.setPen(QPen(QColor("#333"), 15));
	p.drawArc(r.adjusted(15, 15,-15,-15), startangle, -arcsize);

	if(hover) p.setPen(QPen(color.lighter(120), 15));
	else p.setPen(QPen(color, 15));

	auto perc = value()*barsize;
	p.drawArc(r.adjusted(15, 15,-15,-15), startangle-perc-barsize, barsize);
}