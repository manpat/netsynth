#include "customdial.h"
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionSlider>
#include <QtCore/QDebug>

// http://stackoverflow.com/questions/2202717/for-qt-4-6-x-how-to-auto-size-text-to-fit-in-a-specified-width
static void adaptFontSize(QPainter* painter, QRectF drawRect, QString text){
	int flags = Qt::TextDontClip|Qt::TextWordWrap|Qt::AlignCenter;
	QRect fontBoundRect = 
		painter->fontMetrics().boundingRect(drawRect.toRect(), flags, text);
	float xFactor = drawRect.width() / fontBoundRect.width();
	float yFactor = drawRect.height() / fontBoundRect.height();
	float factor = xFactor < yFactor ? xFactor : yFactor;
	QFont f = painter->font();
	f.setPointSizeF(f.pointSizeF()*factor);
	painter->setFont(f);
}

BaseDial::BaseDial(QWidget* p) : QDial(p), color("#3d3"), text("") {}

void BaseDial::setColor(const QColor& c){
	color = c;
}
void BaseDial::setText(const QString& c){
	text = c;
}

AnalogDial::AnalogDial(QWidget* p) : BaseDial(p) {}

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
	const auto offy = 10;

	auto r = style.rect;
	r.adjust(diffx, diffy+offy,-diffx,-diffy+offy); // Squarify

	p.setPen(Qt::NoPen);
	p.setBrush(brush);
	const auto gap = 90 *16;
	const auto arcsize = 360*16-gap;
	const auto startangle = 270*16 - gap/2;

	p.drawPie(r.adjusted(25, 25,-25,-25), startangle, -arcsize);

	r.adjust(15, 15,-15,-15);
	p.setPen(QPen(QColor("#333"), 15));
	p.drawArc(r, startangle, -arcsize);

	if(hover) p.setPen(QPen(color.lighter(120), 15));
	else p.setPen(QPen(color, 15));
	p.drawArc(r, startangle, -arcsize*value()/100);

	r.adjust(20, 20,-20,-20);
	auto font = p.font();
	font.setWeight(QFont::Bold);
	font.setPointSize(16);
	p.setFont(font);
	adaptFontSize(&p, r, text);
	p.setPen(QPen(QColor("#999"), 15));
	p.drawText(r, Qt::AlignCenter, text);
}


DiscreteDial::DiscreteDial(QWidget* p) : BaseDial(p) {
	setSteps(5);
}
void DiscreteDial::setSteps(int s){
	setRange(0, s-1);
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
	const auto offy = 10;

	auto r = style.rect;
	r.adjust(diffx, diffy+offy,-diffx,-diffy+offy); // Squarify

	// Note: angles in 1/16ths of a degree
	p.setPen(Qt::NoPen);
	p.setBrush(brush);
	p.drawEllipse(r.adjusted(25, 25,-25,-25));

	const auto gap = 90 *16;
	const auto arcsize = 360*16-gap;
	const auto startangle = 270*16 - gap/2;
	const auto barsize = arcsize/(maximum()+1);

	r.adjust(15, 15,-15,-15);

	p.setPen(QPen(QColor("#333"), 15));
	p.drawArc(r, startangle, -arcsize);

	if(hover) p.setPen(QPen(color.lighter(120), 15));
	else p.setPen(QPen(color, 15));

	auto perc = value()*barsize;
	p.drawArc(r, startangle-perc-barsize, barsize);

	r.adjust(20, 20,-20,-20);

	auto font = p.font();
	font.setWeight(QFont::Bold);
	font.setPointSize(16);
	p.setFont(font);
	adaptFontSize(&p, r, text);
	p.setPen(QPen(QColor("#999"), 15));
	p.drawText(r, Qt::AlignCenter, text);
}