#include "customdial.h"
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionSlider>
#include <QtCore/QDebug>

// http://stackoverflow.com/questions/2202717/for-qt-4-6-x-how-to-auto-size-text-to-fit-in-a-specified-width
static void adaptFontSize(QPainter* painter, QFont& f, QRectF drawRect, QString text){
	int flags = Qt::TextDontClip|Qt::TextWordWrap;
	QRect fontBoundRect = 
		painter->fontMetrics().boundingRect(drawRect.toRect(), flags, text);
	float xFactor = drawRect.width() / fontBoundRect.width();
	float yFactor = drawRect.height() / fontBoundRect.height();
	float factor = xFactor < yFactor ? xFactor : yFactor;
	f.setPointSizeF(f.pointSizeF()*factor);
}

BaseDial::BaseDial(QWidget* p) : QDial(p), color("#3d3"), text(""), name("") {}

void BaseDial::setColor(const QColor& c){
	color = c;
}
void BaseDial::setText(const QString& c){
	text = c;
}
void BaseDial::setName(const QString& c){
	name = c;
}

void BaseDial::DrawText(QPainter* p, const QRect& r){
	auto textRect = r.adjusted(30, 20,-30,-20);
	auto font = p->font();
	font.setWeight(QFont::Bold);
	adaptFontSize(p, font, textRect, text);
	p->setFont(font);
	p->setPen(QColor("#999"));
	p->drawText(textRect, Qt::AlignCenter, text);

	auto nameRect = r.adjusted(0, r.height()*88/100, 0, 0);
	font.setWeight(QFont::Normal);
	adaptFontSize(p, font, nameRect, name);
	p->setFont(font);
	p->drawText(nameRect, Qt::AlignCenter, name);
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
	const auto offy = 5;

	auto r = style.rect;
	r.adjust(diffx, diffy+offy,-diffx,-diffy+offy); // Squarify
	auto textRect = r.adjusted(15, 5,-15,-5);

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
	p.drawArc(r, startangle, -arcsize*(value()-minimum())/(maximum()-minimum()));

	DrawText(&p, textRect);
}


DiscreteDial::DiscreteDial(QWidget* p) : BaseDial(p) {
	setSteps(5);
	setPageStep(1);
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
	const auto offy = 5;

	auto r = style.rect;
	r.adjust(diffx, diffy+offy,-diffx,-diffy+offy); // Squarify
	auto textRect = r.adjusted(5, 5,-5,-5);

	// Note: angles in 1/16ths of a degree
	p.setPen(Qt::NoPen);
	p.setBrush(brush);
	p.drawEllipse(r.adjusted(25, 25,-25,-25));

	const auto gap = 90 *16;
	const auto arcsize = 360*16-gap;
	const auto startangle = 270*16 - gap/2;
	const auto barsize = arcsize/(maximum()-minimum()+1);

	r.adjust(15, 15,-15,-15);

	p.setPen(QPen(QColor("#333"), 15));
	p.drawArc(r, startangle, -arcsize);

	if(hover) p.setPen(QPen(color.lighter(120), 15));
	else p.setPen(QPen(color, 15));

	auto perc = (value()-minimum())*barsize;
	p.drawArc(r, startangle-perc-barsize, barsize);

	DrawText(&p, textRect);
}