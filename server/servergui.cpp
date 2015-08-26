#include "moc_servergui.h"
#include "visualizationslider.h"

#include <QtGui/QHBoxLayout>

#ifdef _WIN32
#include <time.h>
#endif

ServerGUI::ServerGUI(QWidget* p) : QWidget(p) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
#ifdef _WIN32
	srand(time(nullptr));
#endif

	layout = new QHBoxLayout();

	layout->setContentsMargins(20, 20, 20, 20);
}

void ServerGUI::AddSlider(u32 id) {
	sliders[id] = new VisualizationSlider();
	
	sliders[id]->setMaximumWidth(100);
	sliders[id]->setMinimumWidth(1);
	sliders[id]->setMinimumHeight(15);
	sliders[id]->setRange(0, 100);
	sliders[id]->setSliderPosition(0);
	sliders[id]->setColor(QColor::fromHsv(rand() % 360, 196, 221));
	
	sliders[id]->setText("unnamed");

	layout->addWidget(sliders[id]);

	this->setLayout(layout);
}

void ServerGUI::UpdateSliderText(u32 id, QString text) {
	sliders[id]->setText(text);
}

void ServerGUI::UpdateSliderValue(u32 id, u32 val) {
	sliders[id]->setSliderPosition(val);
}

void ServerGUI::RemoveSlider(u32 id) {
	layout->removeWidget(sliders[id]);
	sliders[id]->deleteLater();
	sliders.erase(id);

	this->setLayout(layout);
}