#include "moc_servergui.h"

#include <QtGui/QHBoxLayout>

#include "visualizationslider.h"

ServerGUI::ServerGUI(QWidget* p) : QWidget(p) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	layout = new QHBoxLayout();
}

void ServerGUI::AddSlider(u32 id) {
	sliders[id] = new VisualizationSlider();
	
	sliders[id]->setBaseSize(1, 10);
	sliders[id]->setRange(0, 100);
	sliders[id]->setSliderPosition(0);

	layout->addWidget(sliders[id]);

	this->setLayout(layout);
}

void ServerGUI::UpdateSlider(u32 id, u32 val) {
	sliders[id]->setSliderPosition(val);
}

void ServerGUI::RemoveSlider(u32 id) {
	layout->removeWidget(sliders[id]);
	sliders.erase(id);

	this->setLayout(layout);
}